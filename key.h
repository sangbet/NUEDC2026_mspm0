#ifndef KEY_H
#define KEY_H

#include <stdbool.h>
#include "motor.h"

// 初始化按键
void Key_Init(void);

// 检测按键是否被有效按下一次（内部包含消抖，读取后自动清除标志）
bool Key_IsPressed(void);

#endif // KEY_H
