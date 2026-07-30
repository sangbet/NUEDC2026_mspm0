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

typedef enum {
    STATE_A = 0,
    STATE_B,
    STATE_C,
    STATE_NUM
} SystemState_t;

static bool is_running = false;
uint32_t trackData[8];
int32_t trackDir;


static SystemState_t current_state = STATE_NUM;
int main(void) {
    SYSCFG_DL_init();
    
    OLED_Init();
    OLED_ColorTurn(0);
    OLED_DisplayTurn(0);
    MotorInit();
    DL_GPIO_setPins(MOTOR_LED_PORT, MOTOR_LED_PIN);


    // SetSpeed(MOTOR_ALL, 0);
    OLED_ShowString(0, 0, (u8 *)"Press Key", 16);
    OLED_Refresh();
    while (1) {
        Key_Scan();

        if (Key0_IsPressed()) {
            current_state++;
            if (current_state >= STATE_NUM) {
                current_state = STATE_A;
            }
        OLED_Clear();
            switch (current_state) {
                case STATE_A: OLED_ShowString(0, 0, (u8 *)"STATE A", 16); break;
                case STATE_B: OLED_ShowString(0, 0, (u8 *)"STATE B", 16); break;
                case STATE_C: OLED_ShowString(0, 0, (u8 *)"STATE C", 16); break;
                default: break;
            }
        OLED_Refresh();
        }

        if (Key1_IsPressed()) {
            // if (current_state == STATE_A) {
            //     DL_GPIO_togglePins(MOTOR_LED_PORT, MOTOR_LED_PIN);
            //     is_running = !is_running;
            // }
            DL_GPIO_togglePins(MOTOR_LED_PORT, MOTOR_LED_PIN);
            is_running = !is_running;
        }

        
        switch (current_state) {
            case STATE_A:
                if (is_running) {
                    ReadTrack(trackData);
                    trackDir = CalTrackDir(trackData);
                    DiffSpeed(1300, 120, trackDir);
                    if (trackDir > 15) {
                        is_running = !is_running;
                        StopMotor(MOTOR_ALL);
                    }
                } else {
                    StopMotor(MOTOR_ALL);
                }
                break;

            case STATE_B:
                if (is_running) {
                    ReadTrack(trackData);
                    trackDir = CalTrackDir(trackData);
                    DiffSpeed(1500, 100, trackDir);
                } else {
                    StopMotor(MOTOR_ALL);
                }
                break;

            case STATE_C:
                // 状态 C 强制停车
                StopMotor(MOTOR_ALL);
                break;

            default:
                // 异常状态保护，强制停车
                StopMotor(MOTOR_ALL);
                break;
        }

    }
}