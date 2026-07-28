/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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

#include "ti_msp_dl_config.h"

#include "motor.h"
#include "track.h"
#include "uart.h"

int main(void)
{
    SYSCFG_DL_init();
    MotorInit();
    NVIC_EnableIRQ(UART2_INST_INT_IRQN);
    DL_UART_enableInterrupt(UART2_INST, DL_UART_INTERRUPT_RX);



    DL_GPIO_clearPins(MOTOR_LED_PORT, MOTOR_LED_PIN);
    // uint32_t trackData[5];
    // int32_t trackDir;
    SetSpeed(MOTOR_ALL, 0);
    
    while (1) {
        UartProcess();
        if (g_uartParsed.updated == true) {
            g_uartParsed.updated = false; // 清除标志

            // 3. 根据解析结果执行具体业务逻辑
            if (g_uartParsed.cmd == 'S') {
                // 处理 $S500,200
                SetSpeed(MOTOR_L, g_uartParsed.param1);
                SetSpeed(MOTOR_R, g_uartParsed.param2);
                
            } else if (g_uartParsed.cmd == 'D') {
                // 处理 $D1200,200
                // SetDistance(g_uartParsed.param1, g_uartParsed.param2);
            }
        }
    }
}
