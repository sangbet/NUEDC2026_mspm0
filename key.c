#include "key.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/driverlib.h>


static volatile bool g_key_int_occurred = false;


void GPIOA_IRQHandler(void) {
    uint32_t intStatus = DL_GPIO_getRawInterruptStatus(GPIOA, DL_GPIO_PIN_ALL);
    
    // 检查是否是 PA09 触发的中断
    if (intStatus & DL_GPIO_PIN_9) {
        g_key_int_occurred = true;
    }
    
    // 【关键修复】清除 GPIOA 端口的所有中断标志位，防止残留标志导致死循环
    DL_GPIO_clearInterruptStatus(GPIOA, intStatus); 
}


void Key_Init(void)
{
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
}


bool Key_IsPressed(void)
{
    bool event_occurred = false;
    // DL_GPIO_togglePins(MOTOR_LED_PORT, MOTOR_LED_PIN);
    __disable_irq();
    event_occurred = g_key_int_occurred;
    g_key_int_occurred = false;
    __enable_irq();

    if (!event_occurred) {
        return false;
    }
    UserDelay(20); 
    if (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_9) == 0) 
    {
        return true;
    }
    
    return false;
}
