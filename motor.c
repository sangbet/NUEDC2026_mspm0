#include "motor.h"

void UserDelay(uint16_t time){
    delay_cycles(time*CPUCLK_FREQ);
}


void MotorInit(){
    DL_GPIO_setPins(MOTOR_STBY_PORT, MOTOR_STBY_PIN);
    DL_GPIO_setPins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
    DL_GPIO_setPins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
    DL_GPIO_clearPins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
    DL_GPIO_clearPins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
    DL_Timer_setCaptureCompareValue(PWMA_INST, 0, GPIO_PWMA);
    DL_Timer_setCaptureCompareValue(PWMB_INST, 0, GPIO_PWMB);
}

void StopMotor(uint8_t motorNum){
    if (motorNum == MOTOR_L || motorNum == MOTOR_ALL) {
        DL_GPIO_clearPins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
        DL_GPIO_clearPins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
    }
    if (motorNum == MOTOR_R || motorNum == MOTOR_ALL) {
        DL_GPIO_clearPins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
        DL_GPIO_clearPins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
    }
}

void ToggleDir(uint8_t motorNum){
    if(motorNum == MOTOR_L){
        DL_GPIO_togglePins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
        DL_GPIO_togglePins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
    }else if(motorNum == MOTOR_R){
        DL_GPIO_togglePins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
        DL_GPIO_togglePins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
    }else if(motorNum == MOTOR_ALL){
        DL_GPIO_togglePins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
        DL_GPIO_togglePins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
        DL_GPIO_togglePins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
        DL_GPIO_togglePins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
    }
}

void SetDir(uint8_t motorNum, uint8_t dir) {
    if (motorNum == MOTOR_L || motorNum == MOTOR_ALL) {
        if (dir == BACKWARD) {
            DL_GPIO_setPins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
            DL_GPIO_clearPins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
        } else {
            DL_GPIO_setPins(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN);
            DL_GPIO_clearPins(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN);
        }
    }
    
    if (motorNum == MOTOR_R || motorNum == MOTOR_ALL) {
        if (dir == BACKWARD) {
            DL_GPIO_setPins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
            DL_GPIO_clearPins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
        } else {
            DL_GPIO_setPins(MOTOR_BIN1_PORT, MOTOR_BIN1_PIN);
            DL_GPIO_clearPins(MOTOR_BIN2_PORT, MOTOR_BIN2_PIN);
        }
    }
}

void SetSpeed(uint8_t motorNum, int32_t speed) {
    uint8_t dir = (speed >= 0) ? FORWARD : BACKWARD;
    int32_t absSpeed = (speed >= 0) ? speed : -speed;
    if (motorNum == MOTOR_L || motorNum == MOTOR_ALL) {
        SetDir(MOTOR_L, dir); 
        DL_Timer_setCaptureCompareValue(PWMA_INST, absSpeed, GPIO_PWMA);
    }

    if (motorNum == MOTOR_R || motorNum == MOTOR_ALL) {
        SetDir(MOTOR_R, dir);
        DL_Timer_setCaptureCompareValue(PWMB_INST, absSpeed, GPIO_PWMB); 
    }
}