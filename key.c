#include "key.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/driverlib.h>

// 简单的微秒/毫秒级延时函数（用于消抖等待）
static void Key_Delay(void) {
    for (volatile uint32_t i = 0; i < 20000; i++) {
        __NOP();
    }
}

void Key0_Init(void) {
    // 纯轮询模式下，不需要开启GPIO中断，所以这里留空
    // 引脚的输入方向、上下拉由 SysConfig (SYSCFG_DL_init) 配置
}

bool Key0_IsPressed(void) {
    // 假设按键按下时引脚为低电平 (0)
    // 如果你的硬件是按下为高电平，请把下面的 == 0 改为 != 0
    if ((DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_25) & DL_GPIO_PIN_25) == 0) {
        
        // 延时约 10-20ms 消抖
        Key_Delay();
        
        // 再次检查引脚状态
        if ((DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_25) & DL_GPIO_PIN_25) == 0) {
            
            // 等待按键松开，防止按住不放导致状态一直跳变
            while ((DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_25) & DL_GPIO_PIN_25) == 0) {
                // 可以在这里加一个超时退出机制，防止死等，但一般测试不需要
            }
            
            return true; // 确认是一次有效的按下并松开
        }
    }
    return false;
}
