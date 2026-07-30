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
#include <stdio.h>
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

// 系统滴答定时器变量
volatile uint32_t g_ulSystemTicks = 0;
void SysTick_Handler(void) {
    g_ulSystemTicks++; // 1ms 中断一次
}

// 【修改点1】初始状态设为 STATE_A，确保上电后处于有效状态
static SystemState_t current_state = STATE_A; 

int main(void) {
    SYSCFG_DL_init();
    // 初始化 SysTick，开启1ms定时中断
    SysTick_Config(CPUCLK_FREQ / 1000);
    
    OLED_Init();
    OLED_ColorTurn(0);
    OLED_DisplayTurn(0);
    MotorInit();
    DL_GPIO_setPins(MOTOR_LED_PORT, MOTOR_LED_PIN);

    uint32_t start_time = 0;
    uint32_t end_time = 0;
    bool prev_running = false;
    
    // 用于记录上一次显示的秒数，只有秒数变化才刷新
    uint32_t last_display_sec = 0xFFFFFFFF; 
    char time_buf[20];

    OLED_ShowString(0, 0, (u8 *)"Press Key", 16);
    sprintf(time_buf, "Time: 0s");
    OLED_ShowString(0, 16, (u8 *)time_buf, 16);
    OLED_Refresh();

    while (1) {
        Key_Scan();

        // 模式切换逻辑
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
            OLED_ShowString(0, 16, (u8 *)time_buf, 16);
            OLED_Refresh();
            // 切换界面时重置秒数记录，防止切换后秒数不变导致不刷新
            last_display_sec = 0xFFFFFFFF; 
        }

        // 启停控制逻辑
        if (Key1_IsPressed()) {
            DL_GPIO_togglePins(MOTOR_LED_PORT, MOTOR_LED_PIN);
            is_running = !is_running;
        }

        // 计时逻辑
        if (is_running) {
            if (!prev_running) {
                start_time = g_ulSystemTicks; // 刚启动，记录起始时间
            }
            end_time = g_ulSystemTicks; // 持续更新结束时间
        }
        prev_running = is_running;

        // 【修改点2】显示逻辑优化：每秒刷新一次，只显示整数秒
        uint32_t display_ms = end_time - start_time;
        uint32_t sec = display_ms / 1000; // 只取整数秒

        if (sec != last_display_sec) {
            last_display_sec = sec;
            sprintf(time_buf, "Time: %us", (unsigned int)sec); // 格式化为整数
            OLED_ShowString(0, 16, (u8 *)time_buf, 16);
            OLED_Refresh(); // 每秒只刷新一次，大大降低CPU占用
        }

        // 电机控制逻辑
        switch (current_state) {
            case STATE_A:
                if (is_running) {
                    ReadTrack(trackData);
                    trackDir = CalTrackDir(trackData);
                    DiffSpeed(1300, 120, trackDir);
                    if (trackDir > 15) {
                        is_running = false; // 建议改为 false，逻辑更严谨
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
                    DiffSpeed(1300, 120, trackDir);
                } else {
                    StopMotor(MOTOR_ALL);
                }
                break;

            case STATE_C:
                StopMotor(MOTOR_ALL);
                break;

            default:
                StopMotor(MOTOR_ALL);
                break;
        }
    }
}