#include "motor.h"


void MotorInit(){
    DL_GPIO_setPins(MOTOR_PORT, MOTOR_STBY_PIN);
    DL_GPIO_setPins(MOTOR_PORT, MOTOR_AIN1_PIN);
    DL_GPIO_setPins(MOTOR_PORT, MOTOR_BIN1_PIN);
    DL_GPIO_clearPins(MOTOR_PORT, MOTOR_AIN2_PIN);
    DL_GPIO_clearPins(MOTOR_PORT, MOTOR_BIN2_PIN);
    DL_Timer_setCaptureCompareValue(PWMA_INST, 0, GPIO_PWMA);
    DL_Timer_setCaptureCompareValue(PWMB_INST, 0, GPIO_PWMB);
}

void ToggleDir(uint8_t motorNum){
    if(motorNum == MOTORL){
        DL_GPIO_togglePins(MOTOR_PORT, MOTOR_AIN1_PIN);
        DL_GPIO_togglePins(MOTOR_PORT, MOTOR_AIN2_PIN);
    }else if(motorNum == MOTORR){
        DL_GPIO_togglePins(MOTOR_PORT, MOTOR_BIN1_PIN);
        DL_GPIO_togglePins(MOTOR_PORT, MOTOR_BIN2_PIN);
    }
}

void SetDir(uint8_t motorNum,uint8_t Dir){
    if(motorNum == MOTORL){
        if(Dir == BACKWARD){
            DL_GPIO_setPins(MOTOR_PORT, MOTOR_AIN2_PIN);
            DL_GPIO_clearPins(MOTOR_PORT, MOTOR_AIN1_PIN);
        }else{
            DL_GPIO_setPins(MOTOR_PORT, MOTOR_AIN1_PIN);
            DL_GPIO_clearPins(MOTOR_PORT, MOTOR_AIN2_PIN);
        }
    }else if(motorNum == MOTORR){
        if(Dir == BACKWARD){
            DL_GPIO_setPins(MOTOR_PORT, MOTOR_BIN2_PIN);
            DL_GPIO_clearPins(MOTOR_PORT, MOTOR_BIN1_PIN);
        }else{
            DL_GPIO_setPins(MOTOR_PORT, MOTOR_BIN1_PIN);
            DL_GPIO_clearPins(MOTOR_PORT, MOTOR_BIN2_PIN);
        }
    }
}
void SetSpeed(int32_t speedL,int32_t speedR){
    int8_t dirL = 0 , dirR = 0;
    if(SpeedL>=0){
        DL_Timer_setCaptureCompareValue(PWMA_INST, speedL, GPIO_PWMA);
    }else{
        DL_Timer_setCaptureCompareValue(PWMA_INST, speedL, GPIO_PWMA);
    }
    if(SpeedR>=0){
        DL_Timer_setCaptureCompareValue(PWMA_INST, speedR, GPIO_PWMA);
    }else{
        DL_Timer_setCaptureCompareValue(PWMA_INST, speedR, GPIO_PWMA);
    }
}