/*
 * spi_wrapper.c
 *
 *  Created on: Jan 22, 2017
 *      Author: VirtWin
 */

#include "spi_wrapper.h"
#include "../util.h"
#include "soc_C6748.h"
#include "hw_psc_C6748.h"
#include "lcdkC6748.h"
#include "spi.h"
#include "psc.h"
#include "edma.h"
#include "edma_event.h"
#include "interrupt.h"
#include <stdbool.h>
#include "hw_types.h"
#include <string.h>
#include "dspcache.h"
#include "../edma3_wrapper/edma3_wrapper.h"

/******************************************************************************/
/*                      INTERNAL MACRO DEFINITIONS                            */
/******************************************************************************/
/* value to configure SMIO,SOMI,CLK and CS pin as functional pin */
#define SIMO_SOMI_CLK_CS        (0x00000E30)
#define CHAR_LENGTH             (0x8)
#define	DATA_FORMAT             SPI_DATA_FORMAT0
#define SPI_REG                 SOC_SPI_0_REGS
#define SPI_CS0                 (0x10)
#define SPI_CS1                 (0x20)
#define SPI_SCLK_HZ             (5000000)

/****************************************************************************/
/*                      INTERNAL GLOBAL VARIABLES                           */
/****************************************************************************/
static bool init_done = 0;
static volatile bool tx_flag = 0;
static volatile bool rx_flag = 0;

/******************************************************************************/
/*                      INTERNAL FUNCTION DEFINITIONS                         */
/******************************************************************************/
/*
** This function is used as a callback from EDMA3 Completion Handler.
** The DMA Mode operation of SPI0 is disabled over here.
*/
static
void
callback (
    unsigned int tcc_num,
    unsigned int status
    )
{
    switch (tcc_num)
    {
        case EDMA3_CHA_SPI0_RX:
            rx_flag = 1;
            /* Disable SPI-EDMA Communication. */
            SPIIntDisable(SPI_REG, SPI_DMA_REQUEST_ENA_INT);
            break;

        case EDMA3_CHA_SPI0_TX:
            tx_flag = 1;
            /* Disable SPI-EDMA Communication. */
            SPIIntDisable(SPI_REG, SPI_DMA_REQUEST_ENA_INT);
            break;

        default:
            break;
    }
}
/*
** This function is used to set the PaRAM entries of EDMA3 for the Transmit
** Channel of SPI0. The corresponding EDMA3 channel is also enabled for
** transmission.
*/
static
int
edma3_param_set_spi_tx (
    unsigned int tcc_num,
    unsigned int channel_num,
    char volatile * buffer,
    unsigned short length
    )
{
    int ret_val;

    ret_val = edma3_param_set(tcc_num, channel_num, buffer, (char volatile *)(SPI_REG + SPI_SPIDAT1), 1, length, 1, 1, 0);

    if (ret_val == EDMA3_OK)
    {
        return SPI_OK;
    }
    else
    {
        ERROR_PRINT("edma3_param_set returned as not OK with error code: %d", ret_val);
        return SPI_INTERNAL_FAILURE_EDMA3_PARAM_SET_FAILED;
    }
}

/*
** This function is used to set the PaRAM entries of EDMA3 for the Receive
** Channel of SPI0. The corresponding EDMA3 channel is also enabled for
** reception.
*/

static
int
edma3_param_set_spi_rx (
    unsigned int tcc_num,
    unsigned int channel_num,
    char volatile * buffer,
    unsigned short length,
    unsigned int dest_bidx_flag
    )
{
    int ret_val;

    ret_val = edma3_param_set(tcc_num, channel_num, (char volatile *) (SPI_REG + SPI_SPIBUF), buffer, 1, length, 1, 0, 1);

    if (ret_val == EDMA3_OK)
    {
        return SPI_OK;
    }
    else
    {
        ERROR_PRINT("edma3_param_set returned as not OK with error code: %d", ret_val);
        return SPI_INTERNAL_FAILURE_EDMA3_PARAM_SET_FAILED;
    }
}

/*
 * Configures SPI Controller.
 */
static
void
spi_setup (
    void
    )
{
    unsigned int val = SIMO_SOMI_CLK_CS;

    /*
     * Waking up the SPI0 instance.
     */
    PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_SPI0, PSC_POWERDOMAIN_ALWAYS_ON,
                     PSC_MDCTL_NEXT_ENABLE);

    /*
     * Performing the Pin Multiplexing for SPI0.
     */
    SPIPinMuxSetup(0);

    /*
     * Using the Chip Select(CS) 5 and 4 pin of SPI0.
     */
    SPI0CSPinMuxSetup(5);
    SPI0CSPinMuxSetup(4);

    SPIReset(SPI_REG);

    SPIOutOfReset(SPI_REG);

    SPIModeConfigure(SPI_REG, SPI_MASTER_MODE);

    SPIPinControl(SPI_REG, 0, 0, &val);

    SPIClkConfigure(SPI_REG, 150000000, SPI_SCLK_HZ, DATA_FORMAT);

    /*
     * Configures SPI Data Format Register
     */

    /*
     * Configures the polarity and phase of SPI clock
     */
    SPIConfigClkFormat(SPI_REG,
                        (SPI_CLK_POL_HIGH | SPI_CLK_OUTOFPHASE),
                        DATA_FORMAT);

    /*
     * Configures SPI to transmit MSB bit First during data transfer
     */
    SPIShiftMsbFirst(SPI_REG, DATA_FORMAT);

    /*
     * Sets the Charcter length
     */
    SPICharLengthSet(SPI_REG, CHAR_LENGTH, DATA_FORMAT);

    //SPIDefaultCSSet(SPI_REG, dcs);

     /*
      * Selects the SPI Data format register to use and add max delay
      * between transactions.
      */
    SPIDat1Config(SPI_REG, (SPI_SPIDAT1_WDEL | DATA_FORMAT), 0);

    /*
     * Maximum delay from CS edges to start and end of transmission
     * of data.
     */
    SPIDelayConfigure(SPI_REG, 0, 0, 0x0, 0x0);

    /*
     * Delay between transactions (max ammount of delay).
     */
    //SPIWdelaySet(SPI_REG, 0x3F, DATA_FORMAT);

    /*
     * Enable SPI communication
     */
    SPIEnable(SPI_REG);
}

/******************************************************************************/
/*                          FUNCTION DEFINITIONS                              */
/******************************************************************************/
int
spi_init (
    void
    )
{
    if (init_done)
    {
        DEBUG_PRINT("SPI is already initialized!\n");
        return SPI_ALREADY_INITIALIZED;
    }

    DEBUG_PRINT("Initializing spi...\n");

    /*
     * Initialize the EDMA3 instance.
     */
    edma3_init();

    /*
     * Initialize SPI w/ Interrupts.
     */
    spi_setup();

    /*
     * Request EDMA3CC for Tx an Rx channels for SPI0.
     */
    edma3_request_channel(EDMA3_CHA_SPI0_TX, EDMA3_CHA_SPI0_TX);
    edma3_request_channel(EDMA3_CHA_SPI0_RX, EDMA3_CHA_SPI0_RX);

    /* Registering Callback Function for Tx and Rx. */
    edma3_set_callback(EDMA3_CHA_SPI0_TX, &callback);
    edma3_set_callback(EDMA3_CHA_SPI0_RX, &callback);

    init_done = 1;

    DEBUG_PRINT("Done initializing spi!\n");

    return SPI_OK;
}

/*
 * Enables SPI Transmit and Receive interrupt.
 * Deasserts Chip Select line.
 *
 * CS should be 0 or 1 only.
 */
int
spi_send_and_receive (
    char volatile * data,
    unsigned int len,
    unsigned int cs
    )
{
    int ret_val;

    if (init_done == 0)
    {
        ERROR_PRINT("SPI is not initialized!\n");
        return SPI_NOT_INTIAILZED;
    }

    if (cs > 1)
    {
        ERROR_PRINT("CS is not 0 or 1; Only supporting 2 CS (Got: %d)", cs);
        return SPI_INVALID_CS;
    }

    /*
     * Get actual cs pin mask.
     */
    switch (cs)
    {
        case 0:
            cs = SPI_CS0;
            break;
        case 1:
            cs = SPI_CS1;
            break;
        default:
            // Wont ever get here
            ERROR_PRINT("SHOULD NEVER BE HERE!?!?!?!?!?!?!??! cs = %d\n", cs);
            break;
    }

    /*
     * Writeback whatever is in cache to main memory.
     */
    CacheWB((unsigned int) data, len);

    DEBUG_PRINT("Sending and receiving spi data with cs: %d\n", cs);
    DEBUG_PRINT("Transaction starting...\n");

    /* Configure the PaRAM registers in EDMA for Transmission.*/
    ret_val = edma3_param_set_spi_tx(EDMA3_CHA_SPI0_TX, EDMA3_CHA_SPI0_TX, data, len);
    if (ret_val != SPI_OK)
    {
        return ret_val;
    }

    /* Configure the PaRAM registers in EDMA for Reception.*/
    ret_val = edma3_param_set_spi_rx(EDMA3_CHA_SPI0_RX, EDMA3_CHA_SPI0_RX, data, len, 1);
    if (ret_val != SPI_OK)
    {
        return ret_val;
    }
    /*
     * Assert the CS pin.
     */
    SPIDat1Config(SPI_REG, (SPI_SPIDAT1_WDEL
                | SPI_SPIDAT1_CSHOLD | DATA_FORMAT), cs);

    /*
     * Enable the interrupts.
     */
    SPIIntEnable(SPI_REG, SPI_DMA_REQUEST_ENA_INT);


    /* Wait until both the flags are set to 1 in the callback function. */
	while ((0 == tx_flag) || (0 == rx_flag));
	tx_flag = 0;
	rx_flag = 0;

    /*
     * Deasserts the CS pin. (Notice no CSHOLD flag)
     */
    SPIDat1Config(SPI_REG, (SPI_SPIDAT1_WDEL
                | DATA_FORMAT), cs);

    DEBUG_PRINT("Transaction finished!\n");

    return SPI_OK;
}
