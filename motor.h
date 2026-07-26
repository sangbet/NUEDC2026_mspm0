#ifndef MOTOR_H
#define MOTOR_H

#define GPIO_PWMA GPIO_PWMA_C1_IDX
#define GPIO_PWMB  GPIO_PWMB_C0_IDX

#define MOTORL 0
#define MOTORR 1

#define FORWARD 1
#define BACKWARD 2

#include "ti_msp_dl_config.h"

void MotorInit();

/**
 *  @brief      用于反转电机的方向
 *  @param  motorNum   电机编号
 *  @note       直接反转AIN1，AIN2或BIN1,BIN2
 */
void ToggleDir(uint8_t motorNum);
void SetDir(uint8_t motorNum,uint8_t Dir);
/**
 *  @brief      用于控制两个电机的转速
 *  @param  speedL   左电机转速
 *  @param  speedR   右电机转速
 *  @note       设置的转速并非实际速度,范围在正负4000之间，函数包括
 */
void SetSpeed(int32_t speedL,int32_t speedR);

#endif