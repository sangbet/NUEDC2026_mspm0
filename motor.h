#ifndef MOTOR_H
#define MOTOR_H

#define GPIO_PWMA GPIO_PWMA_C1_IDX
#define GPIO_PWMB  GPIO_PWMB_C0_IDX

#define MOTOR_ALL 0
#define MOTOR_L 1
#define MOTOR_R 2

#define FORWARD 1
#define BACKWARD 2

#define ENCLINE 13

#include "ti_msp_dl_config.h"

extern uint32_t encA;
extern uint32_t encB;

void UserDelay(uint16_t time);

void MotorInit();
void StopMotor(uint8_t motorNum);

/**
 *  @brief      用于反转电机的方向
 *  @param  motorNum   电机编号 MOTORL MOTORR
 *  @note       直接反转AIN1，AIN2或BIN1,BIN2
 */
void ToggleDir(uint8_t motorNum);

/**
 *  @brief      用于控制电机的方向
 *  @param  motorNum   电机编号 (MOTOR_L, MOTOR_R, MOTOR_ALL)
 *  @param  dir     运动方向 FORWARD BACKWARD
 *  @note       直接改变AIN1，AIN2或BIN1,BIN2
 */
void SetDir(uint8_t motorNum,uint8_t dir);


/**
 * @brief 设置电机速度
 * @param motorNum 电机编号 (MOTOR_L, MOTOR_R, MOTOR_ALL)
 * @param speed    速度值。正数=前进，负数=后退,在正负4000之间
 */
void SetSpeed(uint8_t motorNum, int32_t speed);

/**
 *  @brief      差速控制电机
 *  @param  defaultSpeed 默认速度
 *  @param  weight 差速权重
 *  @param  trackDir 循迹模块传入的方向变量
 *  @note       按照方向在默认速度上加减一定值
 */
void DiffSpeed(int32_t defaultSpeed,uint16_t weight,int32_t trackDir);

#endif