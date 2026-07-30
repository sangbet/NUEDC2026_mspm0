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
#include "oled.h"
#include "key.h"
#include "oled.h"
#include "key.h"

typedef enum {
    STATE_A = 0,
    STATE_B,
    STATE_C,
    STATE_NUM
} SystemState_t;


static SystemState_t current_state = STATE_A;
int main(void) {
    SYSCFG_DL_init();
    // __enable_irq();
    
    OLED_Init();
    OLED_ColorTurn(0);
    OLED_DisplayTurn(0);
    MotorInit();
    DL_GPIO_clearPins(MOTOR_LED_PORT, MOTOR_LED_PIN);

    SetSpeed(MOTOR_ALL, 0);
    
    // // 初始化显示 STATE A
    // OLED_ShowString(0, 0, (u8 *)"STATE A", 16);
    // OLED_Refresh();

    while (1) {
        if (Key0_IsPressed()) {
            current_state++;
            if (current_state >= STATE_NUM) {
                current_state = STATE_A;
            }
            
            switch (current_state) {
                case STATE_A:
                    OLED_ShowString(0, 0, (u8 *)"STATE A", 16);
                    break;
                case STATE_B:
                    OLED_ShowString(0, 0, (u8 *)"STATE B", 16);
                    break;
                case STATE_C:
                    OLED_ShowString(0, 0, (u8 *)"STATE C", 16);
                    break;
                default: break;
            }
            OLED_Refresh();
        }
    }
}