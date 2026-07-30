#ifndef KEY_H
#define KEY_H

#include <stdbool.h>

// 检测 KEY0 是否被有效按下一次（包含消抖，读取后自动清除标志）
bool Key0_IsPressed(void);

#endif // KEY_H