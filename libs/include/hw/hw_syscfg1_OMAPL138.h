/**
 * \name  hw_syscfg1_OMAPL138.h
 *
 * \brief Hardware definitions for OMAPL138
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _HW_SYSCFG1_H_
#define _HW_SYSCFG1_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SYSCFG1_VTPIO_CTL	(0x0)
#define SYSCFG1_DDR_SLEW	(0x4)
#define SYSCFG1_DEEPSLEEP	(0x8)
#define SYSCFG1_PUPD_ENA	(0xC)
#define SYSCFG1_PUPD_SEL	(0x10)
#define SYSCFG1_RXACTIVE	(0x14)
#define SYSCFG1_PWRDN		(0x18)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* VTPIO_CTL */


#define SYSCFG1_VTPIO_CTL_VREFEN (0x00040000u)
#define SYSCFG1_VTPIO_CTL_VREFEN_SHIFT (0x00000012u)

#define SYSCFG1_VTPIO_CTL_VREFTAP (0x00030000u)
#define SYSCFG1_VTPIO_CTL_VREFTAP_SHIFT (0x00000010u)
/*----VREFTAP Tokens----*/
#define SYSCFG1_VTPIO_CTL_VREFTAP_50_0 (0x00000000u)
#define SYSCFG1_VTPIO_CTL_VREFTAP_47_5 (0x00000001u)
#define SYSCFG1_VTPIO_CTL_VREFTAP_52_5 (0x00000002u)

#define SYSCFG1_VTPIO_CTL_READY (0x00008000u)
#define SYSCFG1_VTPIO_CTL_READY_SHIFT (0x0000000Fu)

#define SYSCFG1_VTPIO_CTL_IOPWRDN (0x00004000u)
#define SYSCFG1_VTPIO_CTL_IOPWRDN_SHIFT (0x0000000Eu)

#define SYSCFG1_VTPIO_CTL_CLKRZ (0x00002000u)
#define SYSCFG1_VTPIO_CTL_CLKRZ_SHIFT (0x0000000Du)

#define SYSCFG1_VTPIO_CTL_FORCEDNP (0x00001000u)
#define SYSCFG1_VTPIO_CTL_FORCEDNP_SHIFT (0x0000000Cu)

#define SYSCFG1_VTPIO_CTL_FORCEDNN (0x00000800u)
#define SYSCFG1_VTPIO_CTL_FORCEDNN_SHIFT (0x0000000Bu)

#define SYSCFG1_VTPIO_CTL_FORCEUPP (0x00000400u)
#define SYSCFG1_VTPIO_CTL_FORCEUPP_SHIFT (0x0000000Au)

#define SYSCFG1_VTPIO_CTL_FORCEUPN (0x00000200u)
#define SYSCFG1_VTPIO_CTL_FORCEUPN_SHIFT (0x00000009u)

#define SYSCFG1_VTPIO_CTL_PWRSAVE (0x00000100u)
#define SYSCFG1_VTPIO_CTL_PWRSAVE_SHIFT (0x00000008u)

#define SYSCFG1_VTPIO_CTL_LOCK  (0x00000080u)
#define SYSCFG1_VTPIO_CTL_LOCK_SHIFT (0x00000007u)

#define SYSCFG1_VTPIO_CTL_POWERDN (0x00000040u)
#define SYSCFG1_VTPIO_CTL_POWERDN_SHIFT (0x00000006u)

#define SYSCFG1_VTPIO_CTL_D0    (0x00000020u)
#define SYSCFG1_VTPIO_CTL_D0_SHIFT   (0x00000005u)

#define SYSCFG1_VTPIO_CTL_D1    (0x00000010u)
#define SYSCFG1_VTPIO_CTL_D1_SHIFT   (0x00000004u)

#define SYSCFG1_VTPIO_CTL_D2    (0x00000008u)
#define SYSCFG1_VTPIO_CTL_D2_SHIFT   (0x00000003u)

#define SYSCFG1_VTPIO_CTL_F0    (0x00000004u)
#define SYSCFG1_VTPIO_CTL_F0_SHIFT   (0x00000002u)

#define SYSCFG1_VTPIO_CTL_F1    (0x00000002u)
#define SYSCFG1_VTPIO_CTL_F1_SHIFT   (0x00000001u)

#define SYSCFG1_VTPIO_CTL_F2    (0x00000001u)
#define SYSCFG1_VTPIO_CTL_F2_SHIFT   (0x00000000u)


/* DDR_SLEW */


#define SYSCFG1_DDR_SLEW_ODT_TERMON (0x00000C00u)
#define SYSCFG1_DDR_SLEW_ODT_TERMON_SHIFT (0x0000000Au)

#define SYSCFG1_DDR_SLEW_ODT_TERMOFF (0x00000300u)
#define SYSCFG1_DDR_SLEW_ODT_TERMOFF_SHIFT (0x00000008u)

#define SYSCFG1_DDR_SLEW_DDR_PDENA (0x00000020u)
#define SYSCFG1_DDR_SLEW_DDR_PDENA_SHIFT (0x00000005u)

#define SYSCFG1_DDR_SLEW_CMOSEN (0x00000010u)
#define SYSCFG1_DDR_SLEW_CMOSEN_SHIFT (0x00000004u)

#define SYSCFG1_DDR_SLEW_DDR_DATASLEW (0x0000000Cu)
#define SYSCFG1_DDR_SLEW_DDR_DATASLEW_SHIFT (0x00000002u)

#define SYSCFG1_DDR_SLEW_DDR_CMDSLEW (0x00000003u)
#define SYSCFG1_DDR_SLEW_DDR_CMDSLEW_SHIFT (0x00000000u)

/* DEEPSLEEP */

#define SYSCFG1_DEEPSLEEP_SLEEPENABLE (0x80000000u)
#define SYSCFG1_DEEPSLEEP_SLEEPENABLE_SHIFT (0x0000001Fu)

#define SYSCFG1_DEEPSLEEP_SLEEPCOMPLETE (0x40000000u)
#define SYSCFG1_DEEPSLEEP_SLEEPCOMPLETE_SHIFT (0x0000001Eu)

#define SYSCFG1_DEEPSLEEP_SLEEPCOUNT (0x0000FFFFu)
#define SYSCFG1_DEEPSLEEP_SLEEPCOUNT_SHIFT (0x00000000u)


/* PUPD_ENA */

#define SYSCFG1_PUPD_ENA_PUPDENA31 (0x80000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA31_SHIFT (0x0000001Fu)

#define SYSCFG1_PUPD_ENA_PUPDENA30 (0x40000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA30_SHIFT (0x0000001Eu)

#define SYSCFG1_PUPD_ENA_PUPDENA29 (0x20000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA29_SHIFT (0x0000001Du)

#define SYSCFG1_PUPD_ENA_PUPDENA28 (0x10000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA28_SHIFT (0x0000001Cu)

#define SYSCFG1_PUPD_ENA_PUPDENA27 (0x08000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA27_SHIFT (0x0000001Bu)

#define SYSCFG1_PUPD_ENA_PUPDENA26 (0x04000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA26_SHIFT (0x0000001Au)

#define SYSCFG1_PUPD_ENA_PUPDENA25 (0x02000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA25_SHIFT (0x00000019u)

#define SYSCFG1_PUPD_ENA_PUPDENA24 (0x01000000u)
#define SYSCFG1_PUPD_ENA_PUPDENA24_SHIFT (0x00000018u)

#define SYSCFG1_PUPD_ENA_PUPDENA23 (0x00800000u)
#define SYSCFG1_PUPD_ENA_PUPDENA23_SHIFT (0x00000017u)

#define SYSCFG1_PUPD_ENA_PUPDENA22 (0x00400000u)
#define SYSCFG1_PUPD_ENA_PUPDENA22_SHIFT (0x00000016u)

#define SYSCFG1_PUPD_ENA_PUPDENA21 (0x00200000u)
#define SYSCFG1_PUPD_ENA_PUPDENA21_SHIFT (0x00000015u)

#define SYSCFG1_PUPD_ENA_PUPDENA20 (0x00100000u)
#define SYSCFG1_PUPD_ENA_PUPDENA20_SHIFT (0x00000014u)

#define SYSCFG1_PUPD_ENA_PUPDENA19 (0x00080000u)
#define SYSCFG1_PUPD_ENA_PUPDENA19_SHIFT (0x00000013u)

#define SYSCFG1_PUPD_ENA_PUPDENA18 (0x00040000u)
#define SYSCFG1_PUPD_ENA_PUPDENA18_SHIFT (0x00000012u)

#define SYSCFG1_PUPD_ENA_PUPDENA17 (0x00020000u)
#define SYSCFG1_PUPD_ENA_PUPDENA17_SHIFT (0x00000011u)

#define SYSCFG1_PUPD_ENA_PUPDENA16 (0x00010000u)
#define SYSCFG1_PUPD_ENA_PUPDENA16_SHIFT (0x00000010u)

#define SYSCFG1_PUPD_ENA_PUPDENA15 (0x00008000u)
#define SYSCFG1_PUPD_ENA_PUPDENA15_SHIFT (0x0000000Fu)

#define SYSCFG1_PUPD_ENA_PUPDENA14 (0x00004000u)
#define SYSCFG1_PUPD_ENA_PUPDENA14_SHIFT (0x0000000Eu)

#define SYSCFG1_PUPD_ENA_PUPDENA13 (0x00002000u)
#define SYSCFG1_PUPD_ENA_PUPDENA13_SHIFT (0x0000000Du)

#define SYSCFG1_PUPD_ENA_PUPDENA12 (0x00001000u)
#define SYSCFG1_PUPD_ENA_PUPDENA12_SHIFT (0x0000000Cu)

#define SYSCFG1_PUPD_ENA_PUPDENA11 (0x00000800u)
#define SYSCFG1_PUPD_ENA_PUPDENA11_SHIFT (0x0000000Bu)

#define SYSCFG1_PUPD_ENA_PUPDENA10 (0x00000400u)
#define SYSCFG1_PUPD_ENA_PUPDENA10_SHIFT (0x0000000Au)

#define SYSCFG1_PUPD_ENA_PUPDENA9 (0x00000200u)
#define SYSCFG1_PUPD_ENA_PUPDENA9_SHIFT (0x00000009u)

#define SYSCFG1_PUPD_ENA_PUPDENA8 (0x00000100u)
#define SYSCFG1_PUPD_ENA_PUPDENA8_SHIFT (0x00000008u)

#define SYSCFG1_PUPD_ENA_PUPDENA7 (0x00000080u)
#define SYSCFG1_PUPD_ENA_PUPDENA7_SHIFT (0x00000007u)

#define SYSCFG1_PUPD_ENA_PUPDENA6 (0x00000040u)
#define SYSCFG1_PUPD_ENA_PUPDENA6_SHIFT (0x00000006u)

#define SYSCFG1_PUPD_ENA_PUPDENA5 (0x00000020u)
#define SYSCFG1_PUPD_ENA_PUPDENA5_SHIFT (0x00000005u)

#define SYSCFG1_PUPD_ENA_PUPDENA4 (0x00000010u)
#define SYSCFG1_PUPD_ENA_PUPDENA4_SHIFT (0x00000004u)

#define SYSCFG1_PUPD_ENA_PUPDENA3 (0x00000008u)
#define SYSCFG1_PUPD_ENA_PUPDENA3_SHIFT (0x00000003u)

#define SYSCFG1_PUPD_ENA_PUPDENA2 (0x00000004u)
#define SYSCFG1_PUPD_ENA_PUPDENA2_SHIFT (0x00000002u)

#define SYSCFG1_PUPD_ENA_PUPDENA1 (0x00000002u)
#define SYSCFG1_PUPD_ENA_PUPDENA1_SHIFT (0x00000001u)

#define SYSCFG1_PUPD_ENA_PUPDENA0 (0x00000001u)
#define SYSCFG1_PUPD_ENA_PUPDENA0_SHIFT (0x00000000u)


/* PUPD_SEL */

#define SYSCFG1_PUPD_SEL_PUPDSEL31 (0x80000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL31_SHIFT (0x0000001Fu)

#define SYSCFG1_PUPD_SEL_PUPDSEL30 (0x40000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL30_SHIFT (0x0000001Eu)

#define SYSCFG1_PUPD_SEL_PUPDSEL29 (0x20000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL29_SHIFT (0x0000001Du)

#define SYSCFG1_PUPD_SEL_PUPDSEL28 (0x10000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL28_SHIFT (0x0000001Cu)

#define SYSCFG1_PUPD_SEL_PUPDSEL27 (0x08000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL27_SHIFT (0x0000001Bu)

#define SYSCFG1_PUPD_SEL_PUPDSEL26 (0x04000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL26_SHIFT (0x0000001Au)

#define SYSCFG1_PUPD_SEL_PUPDSEL25 (0x02000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL25_SHIFT (0x00000019u)

#define SYSCFG1_PUPD_SEL_PUPDSEL24 (0x01000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL24_SHIFT (0x00000018u)

#define SYSCFG1_PUPD_SEL_PUPDSEL23 (0x00800000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL23_SHIFT (0x00000017u)

#define SYSCFG1_PUPD_SEL_PUPDSEL22 (0x00400000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL22_SHIFT (0x00000016u)

#define SYSCFG1_PUPD_SEL_PUPDSEL21 (0x00200000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL21_SHIFT (0x00000015u)

#define SYSCFG1_PUPD_SEL_PUPDSEL20 (0x00100000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL20_SHIFT (0x00000014u)

#define SYSCFG1_PUPD_SEL_PUPDSEL19 (0x00080000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL19_SHIFT (0x00000013u)

#define SYSCFG1_PUPD_SEL_PUPDSEL18 (0x00040000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL18_SHIFT (0x00000012u)

#define SYSCFG1_PUPD_SEL_PUPDSEL17 (0x00020000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL17_SHIFT (0x00000011u)

#define SYSCFG1_PUPD_SEL_PUPDSEL16 (0x00010000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL16_SHIFT (0x00000010u)

#define SYSCFG1_PUPD_SEL_PUPDSEL15 (0x00008000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL15_SHIFT (0x0000000Fu)

#define SYSCFG1_PUPD_SEL_PUPDSEL14 (0x00004000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL14_SHIFT (0x0000000Eu)

#define SYSCFG1_PUPD_SEL_PUPDSEL13 (0x00002000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL13_SHIFT (0x0000000Du)

#define SYSCFG1_PUPD_SEL_PUPDSEL12 (0x00001000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL12_SHIFT (0x0000000Cu)

#define SYSCFG1_PUPD_SEL_PUPDSEL11 (0x00000800u)
#define SYSCFG1_PUPD_SEL_PUPDSEL11_SHIFT (0x0000000Bu)

#define SYSCFG1_PUPD_SEL_PUPDSEL10 (0x00000400u)
#define SYSCFG1_PUPD_SEL_PUPDSEL10_SHIFT (0x0000000Au)

#define SYSCFG1_PUPD_SEL_PUPDSEL9 (0x00000200u)
#define SYSCFG1_PUPD_SEL_PUPDSEL9_SHIFT (0x00000009u)

#define SYSCFG1_PUPD_SEL_PUPDSEL8 (0x00000100u)
#define SYSCFG1_PUPD_SEL_PUPDSEL8_SHIFT (0x00000008u)

#define SYSCFG1_PUPD_SEL_PUPDSEL7 (0x00000080u)
#define SYSCFG1_PUPD_SEL_PUPDSEL7_SHIFT (0x00000007u)

#define SYSCFG1_PUPD_SEL_PUPDSEL6 (0x00000040u)
#define SYSCFG1_PUPD_SEL_PUPDSEL6_SHIFT (0x00000006u)

#define SYSCFG1_PUPD_SEL_PUPDSEL5 (0x00000020u)
#define SYSCFG1_PUPD_SEL_PUPDSEL5_SHIFT (0x00000005u)

#define SYSCFG1_PUPD_SEL_PUPDSEL4 (0x00000010u)
#define SYSCFG1_PUPD_SEL_PUPDSEL4_SHIFT (0x00000004u)
/*----PUPDSEL4 Tokens----*/
#define SYSCFG1_PUPD_SEL_PUPDSEL4_PULLDOWN (0x00000000u)
#define SYSCFG1_PUPD_SEL_PUPDSEL4_PULLUP (0x00000001u)

#define SYSCFG1_PUPD_SEL_PUPDSEL3 (0x00000008u)
#define SYSCFG1_PUPD_SEL_PUPDSEL3_SHIFT (0x00000003u)

#define SYSCFG1_PUPD_SEL_PUPDSEL2 (0x00000004u)
#define SYSCFG1_PUPD_SEL_PUPDSEL2_SHIFT (0x00000002u)

#define SYSCFG1_PUPD_SEL_PUPDSEL1 (0x00000002u)
#define SYSCFG1_PUPD_SEL_PUPDSEL1_SHIFT (0x00000001u)

#define SYSCFG1_PUPD_SEL_PUPDSEL0 (0x00000001u)
#define SYSCFG1_PUPD_SEL_PUPDSEL0_SHIFT (0x00000000u)


/* RXACTIVE */

#define SYSCFG1_RXACTIVE_RXACTIVE31 (0x80000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE31_SHIFT (0x0000001Fu)

#define SYSCFG1_RXACTIVE_RXACTIVE30 (0x40000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE30_SHIFT (0x0000001Eu)

#define SYSCFG1_RXACTIVE_RXACTIVE29 (0x20000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE29_SHIFT (0x0000001Du)

#define SYSCFG1_RXACTIVE_RXACTIVE28 (0x10000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE28_SHIFT (0x0000001Cu)

#define SYSCFG1_RXACTIVE_RXACTIVE27 (0x08000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE27_SHIFT (0x0000001Bu)

#define SYSCFG1_RXACTIVE_RXACTIVE26 (0x04000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE26_SHIFT (0x0000001Au)

#define SYSCFG1_RXACTIVE_RXACTIVE25 (0x02000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE25_SHIFT (0x00000019u)

#define SYSCFG1_RXACTIVE_RXACTIVE24 (0x01000000u)
#define SYSCFG1_RXACTIVE_RXACTIVE24_SHIFT (0x00000018u)

#define SYSCFG1_RXACTIVE_RXACTIVE23 (0x00800000u)
#define SYSCFG1_RXACTIVE_RXACTIVE23_SHIFT (0x00000017u)

#define SYSCFG1_RXACTIVE_RXACTIVE22 (0x00400000u)
#define SYSCFG1_RXACTIVE_RXACTIVE22_SHIFT (0x00000016u)

#define SYSCFG1_RXACTIVE_RXACTIVE21 (0x00200000u)
#define SYSCFG1_RXACTIVE_RXACTIVE21_SHIFT (0x00000015u)

#define SYSCFG1_RXACTIVE_RXACTIVE20 (0x00100000u)
#define SYSCFG1_RXACTIVE_RXACTIVE20_SHIFT (0x00000014u)

#define SYSCFG1_RXACTIVE_RXACTIVE19 (0x00080000u)
#define SYSCFG1_RXACTIVE_RXACTIVE19_SHIFT (0x00000013u)

#define SYSCFG1_RXACTIVE_RXACTIVE18 (0x00040000u)
#define SYSCFG1_RXACTIVE_RXACTIVE18_SHIFT (0x00000012u)

#define SYSCFG1_RXACTIVE_RXACTIVE17 (0x00020000u)
#define SYSCFG1_RXACTIVE_RXACTIVE17_SHIFT (0x00000011u)

#define SYSCFG1_RXACTIVE_RXACTIVE16 (0x00010000u)
#define SYSCFG1_RXACTIVE_RXACTIVE16_SHIFT (0x00000010u)

#define SYSCFG1_RXACTIVE_RXACTIVE15 (0x00008000u)
#define SYSCFG1_RXACTIVE_RXACTIVE15_SHIFT (0x0000000Fu)

#define SYSCFG1_RXACTIVE_RXACTIVE14 (0x00004000u)
#define SYSCFG1_RXACTIVE_RXACTIVE14_SHIFT (0x0000000Eu)

#define SYSCFG1_RXACTIVE_RXACTIVE13 (0x00002000u)
#define SYSCFG1_RXACTIVE_RXACTIVE13_SHIFT (0x0000000Du)

#define SYSCFG1_RXACTIVE_RXACTIVE12 (0x00001000u)
#define SYSCFG1_RXACTIVE_RXACTIVE12_SHIFT (0x0000000Cu)

#define SYSCFG1_RXACTIVE_RXACTIVE11 (0x00000800u)
#define SYSCFG1_RXACTIVE_RXACTIVE11_SHIFT (0x0000000Bu)

#define SYSCFG1_RXACTIVE_RXACTIVE10 (0x00000400u)
#define SYSCFG1_RXACTIVE_RXACTIVE10_SHIFT (0x0000000Au)

#define SYSCFG1_RXACTIVE_RXACTIVE9 (0x00000200u)
#define SYSCFG1_RXACTIVE_RXACTIVE9_SHIFT (0x00000009u)

#define SYSCFG1_RXACTIVE_RXACTIVE8 (0x00000100u)
#define SYSCFG1_RXACTIVE_RXACTIVE8_SHIFT (0x00000008u)

#define SYSCFG1_RXACTIVE_RXACTIVE7 (0x00000080u)
#define SYSCFG1_RXACTIVE_RXACTIVE7_SHIFT (0x00000007u)

#define SYSCFG1_RXACTIVE_RXACTIVE6 (0x00000040u)
#define SYSCFG1_RXACTIVE_RXACTIVE6_SHIFT (0x00000006u)

#define SYSCFG1_RXACTIVE_RXACTIVE5 (0x00000020u)
#define SYSCFG1_RXACTIVE_RXACTIVE5_SHIFT (0x00000005u)

#define SYSCFG1_RXACTIVE_RXACTIVE4 (0x00000010u)
#define SYSCFG1_RXACTIVE_RXACTIVE4_SHIFT (0x00000004u)

#define SYSCFG1_RXACTIVE_RXACTIVE3 (0x00000008u)
#define SYSCFG1_RXACTIVE_RXACTIVE3_SHIFT (0x00000003u)

#define SYSCFG1_RXACTIVE_RXACTIVE2 (0x00000004u)
#define SYSCFG1_RXACTIVE_RXACTIVE2_SHIFT (0x00000002u)

#define SYSCFG1_RXACTIVE_RXACTIVE1 (0x00000002u)
#define SYSCFG1_RXACTIVE_RXACTIVE1_SHIFT (0x00000001u)

#define SYSCFG1_RXACTIVE_RXACTIVE0 (0x00000001u)
#define SYSCFG1_RXACTIVE_RXACTIVE0_SHIFT (0x00000000u)

/* PWRDN */


#define SYSCFG1_PWRDN_SATACLK_PWRDN (0x00000001u)
#define SYSCFG1_PWRDN_SATACLK_PWRDN_SHIFT (0x00000000u)

#ifdef __cplusplus
}
#endif

#endif  /* _HW_SYSCFG1_H_ */
