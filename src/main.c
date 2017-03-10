/*
 * main.c
 */

#ifndef _TMS320C6X
#error Macro _TMS320C6X is not defined!
#endif

#include "util.h"
#include "interrupt_wrapper/interrupt_wrapper.h"
#include "uart_wrapper/uart_wrapper.h"
#include "timer_wrapper/timer_wrapper.h"
#include "spi_wrapper/spi_wrapper.h"
#include "dac_wrapper/dac_wrapper.h"
#include "adc_wrapper/adc_wrapper.h"
#include "edma3_wrapper/edma3_wrapper.h"
#include "mcasp_wrapper/mcasp_wrapper.h"
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "soc_C6748.h"

#define CHANNEL_POWER DAC_POWER_ON_CHANNEL_7
#define CHANNEL DAC_ADDRESS_CHANNEL_7

#ifndef PI
#define PI (3.14159265358979323846)
#endif

//
// Output frequency of DAC
//
#define SAMPLING_FREQUENCY (8000)

//
// Single tone frequency
//
#define COS_FREQ           (500)

//
// Do not touch the below two
//
#define NUM_SAMPLES        (SAMPLING_FREQUENCY / COS_FREQ)
#define TIMER_MICROSECONDS (1000000 / SAMPLING_FREQUENCY)

static bool volatile timer_flag = 0;

static
void
timer_function (
    void
    )
{
    timer_flag = 1;
}

int
main (
    void
    )
{
    int ret_val;
    uint16_t mic_data[2];
    int a;
	char buffer[50];
	double x;
	double y;
	uint16_t val[NUM_SAMPLES];
	int i;

    /*
     * Init system interrupts.
     */
    ret_val = init_interrupt();
    ASSERT(ret_val == INTERRUPT_OK, "Interrupt init failed! (%d)\n", ret_val);

    /*
     * Init uart before everything else so debug
     * statements can be seen
     */
    ret_val = uart_init();
    ASSERT(ret_val == UART_OK, "UART Init failed! (%d)\n", ret_val);

    NORMAL_PRINT("Application Starting\n");
    DEBUG_PRINT("Debug prints are enabled\n");

    /*
     * Init system interrupts.
     */
    ret_val = edma3_init();
    ASSERT(ret_val == EDMA3_OK, "EDMA3 init failed! (%d)\n", ret_val);

#if 0
    /*
     * Init McASP
     */
    ret_val = mcasp_init();
    ASSERT(ret_val == DAC_OK, "McASP init failed! (%d)\n", ret_val);

#ifdef MCASP_LOOPBACK_TEST
    /*
     * Loop back test for McASP
     */
    mcasp_loopback_test();
#endif
#endif
    /*
     * Init spi.
     */
    ret_val = spi_init();
    ASSERT(ret_val == SPI_OK, "SPI init failed! (%d)\n", ret_val);

    /*
     * Init dac.
     */
    ret_val = dac_init(1);
    ASSERT(ret_val == DAC_OK, "DAC init failed! (%d)\n", ret_val);

    /*
     * Init adc.
     */
    ret_val = adc_init(0);
    ASSERT(ret_val == ADC_OK, "ADC init failed! (%d)\n", ret_val);

    while (1) {
        uint16_t data;
        ret_val = adc_read(&data);
        ASSERT(ret_val == ADC_OK, "ADC read! (%d)\n", ret_val);

        DEBUG_PRINT("Data read: %u\n", data);
    }
    /*
     * Init Timer
     */
    ret_val = timer_init(&timer_function, TIMER_MICROSECONDS);
    ASSERT(ret_val == TIMER_OK, "Timer Init failed! (%d)\n", ret_val);

    // Power on dac channel
    ret_val = dac_power_up(CHANNEL_POWER);
    ASSERT(ret_val == DAC_OK, "DAC power on failed! (%d)\n", ret_val);

#ifdef DAC_DO_NOT_USE_INTERNAL_REFERENCE
    ret_val = dac_internal_reference_power_down();
    ASSERT(ret_val == DAC_OK, "DAC power on failed! (%d)\n", ret_val);
#endif // #DAC_DO_NOT_USE_INTERNAL_REFERENCE

    //ret_val = dac_update(CHANNEL, (uint16_t) 52628);
    //ASSERT(ret_val == DAC_OK, "DAC update failed! (%d)\n", ret_val);

    //NORMAL_PRINT("DONE\n");
    //while (1);
#ifdef SINGLE_TONE_SIGNAL_THROUGH_DAC
    /*
	 * Pre calculate samples for simple sinusoid output to dac.
	 */
	x = 0;
	for (i = 0; i < NUM_SAMPLES; ++i)
	{
		//y = (cos(2 * COS_FREQ * PI * x) + 1) / 0.00007629394;
		y = (cos(2 * COS_FREQ * PI * x) + 1) * 32767;
		x += 1.0 / SAMPLING_FREQUENCY;
		val[i] = (uint16_t) y;
    }
#endif // #ifdef SINGLE_TONE_SIGNAL_THROUGH_DAC

#if defined(SINGLE_TONE_SIGNAL_THROUGH_DAC) || defined(MIC_TO_DAC)
	i = 0;
    timer_start();
    while (1)
    {
#if 0
        char s[17] = "0000000000000000";
        int cnt = 0;

        ret_val = mcasp_latest_rx_data((uint16_t *) &mic_data);
        ASSERT(ret_val == MCASP_OK, "MCASP getting latest rx data failed! (%d)\n", ret_val);

        s[16] = 0;

        for (i = 0; i < 16; ++i)
        {
            if (mic_data[0] & (0x1 << i))
            {
                s[15 - i] = '1';
                cnt += 1;
            }
        }

        NORMAL_PRINT("%d\n", (((int)mic_data[0]) + 0x8000));
#endif // #if 0

#ifdef SINGLE_TONE_SIGNAL_THROUGH_DAC
        ASSERT(timer_flag == 0, "TIMER IS TOO FAST!\n");
        while (timer_flag == 0);
        timer_flag = 0;

        ret_val = dac_update(CHANNEL, val[i]);
        ASSERT(ret_val == DAC_OK, "DAC update failed! (%d)\n", ret_val);

        if (++i == NUM_SAMPLES)
        {
            i = 0;
        }
#endif // #ifdef SINGLE_TONE_SIGNAL_THROUGH_DAC

#if defined(MIC_TO_DAC) && !defined(SINGLE_TONE_SIGNAL_THROUGH_DAC)
        mic_data[0] = (*((int16_t volatile *) SOC_MCASP_0_DATA_REGS));

        //
        // This adds a Vref/2 DC offset
        //
        ret_val = dac_update(CHANNEL, (mic_data[0] + 0x8000));

        //
        // This is just straight data copy from mcasp registers to dac
        //
        //ret_val = dac_update(CHANNEL, mic_data[0]);

        ASSERT(ret_val == DAC_OK, "DAC update failed! (%d)\n", ret_val);
#endif MIC_TO_DAC
    }
    //timer_stop();
#endif

    /*
     * Loop forever.
     */
    NORMAL_PRINT("Looping forever...\n");
    //while (1);

    return 0;
}
