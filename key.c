#include "key.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/driverlib.h>



// 增加一个静态变量记录上一次的状态
static bool last_key_state = true; // 假设默认高电平

bool Key0_IsPressed(void) {
    bool current_state = (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_25) & DL_GPIO_PIN_25) != 0;
    if (last_key_state == true && current_state == false) {

        last_key_state = current_state;
        return true;
    }
    
    last_key_state = current_state;
    return false;
}
