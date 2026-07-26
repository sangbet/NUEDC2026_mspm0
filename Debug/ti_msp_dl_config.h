/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000
/* Defines for SYSPLL_ERR_01 Workaround */
/* Represent 1.000 as 1000 */
#define FLOAT_TO_INT_SCALE                                               (1000U)
#define FCC_EXPECTED_RATIO                                                  2500
#define FCC_UPPER_BOUND                       (FCC_EXPECTED_RATIO * (1 + 0.003))
#define FCC_LOWER_BOUND                       (FCC_EXPECTED_RATIO * (1 - 0.003))

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);


/* Defines for PWMB */
#define PWMB_INST                                                          TIMA0
#define PWMB_INST_IRQHandler                                    TIMA0_IRQHandler
#define PWMB_INST_INT_IRQN                                      (TIMA0_INT_IRQn)
#define PWMB_INST_CLK_FREQ                                              40000000
/* GPIO defines for channel 0 */
#define GPIO_PWMB_C0_PORT                                                  GPIOB
#define GPIO_PWMB_C0_PIN                                           DL_GPIO_PIN_8
#define GPIO_PWMB_C0_IOMUX                                       (IOMUX_PINCM25)
#define GPIO_PWMB_C0_IOMUX_FUNC                      IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_PWMB_C0_IDX                                     DL_TIMER_CC_0_INDEX

/* Defines for PWMA */
#define PWMA_INST                                                          TIMG6
#define PWMA_INST_IRQHandler                                    TIMG6_IRQHandler
#define PWMA_INST_INT_IRQN                                      (TIMG6_INT_IRQn)
#define PWMA_INST_CLK_FREQ                                              40000000
/* GPIO defines for channel 1 */
#define GPIO_PWMA_C1_PORT                                                  GPIOB
#define GPIO_PWMA_C1_PIN                                           DL_GPIO_PIN_7
#define GPIO_PWMA_C1_IOMUX                                       (IOMUX_PINCM24)
#define GPIO_PWMA_C1_IOMUX_FUNC                      IOMUX_PINCM24_PF_TIMG6_CCP1
#define GPIO_PWMA_C1_IDX                                     DL_TIMER_CC_1_INDEX




/* Defines for BIN2: GPIOB.13 with pinCMx 30 on package pin 1 */
#define MOTOR_BIN2_PORT                                                  (GPIOB)
#define MOTOR_BIN2_PIN                                          (DL_GPIO_PIN_13)
#define MOTOR_BIN2_IOMUX                                         (IOMUX_PINCM30)
/* Defines for BIN1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define MOTOR_BIN1_PORT                                                  (GPIOA)
#define MOTOR_BIN1_PIN                                          (DL_GPIO_PIN_17)
#define MOTOR_BIN1_IOMUX                                         (IOMUX_PINCM39)
/* Defines for STBY: GPIOB.26 with pinCMx 57 on package pin 28 */
#define MOTOR_STBY_PORT                                                  (GPIOB)
#define MOTOR_STBY_PIN                                          (DL_GPIO_PIN_26)
#define MOTOR_STBY_IOMUX                                         (IOMUX_PINCM57)
/* Defines for AIN1: GPIOB.9 with pinCMx 26 on package pin 61 */
#define MOTOR_AIN1_PORT                                                  (GPIOB)
#define MOTOR_AIN1_PIN                                           (DL_GPIO_PIN_9)
#define MOTOR_AIN1_IOMUX                                         (IOMUX_PINCM26)
/* Defines for AIN2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define MOTOR_AIN2_PORT                                                  (GPIOB)
#define MOTOR_AIN2_PIN                                           (DL_GPIO_PIN_6)
#define MOTOR_AIN2_IOMUX                                         (IOMUX_PINCM23)
/* Defines for LED: GPIOB.22 with pinCMx 50 on package pin 21 */
#define MOTOR_LED_PORT                                                   (GPIOB)
#define MOTOR_LED_PIN                                           (DL_GPIO_PIN_22)
#define MOTOR_LED_IOMUX                                          (IOMUX_PINCM50)


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);
void SYSCFG_DL_PWMB_init(void);
void SYSCFG_DL_PWMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
