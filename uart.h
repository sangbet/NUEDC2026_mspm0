#ifndef UART_H
#define UART_H

#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdbool.h>

#define UART2_MAX_LEN 64

// 原始接收数据包结构体
typedef struct {
    uint8_t buffer[UART2_MAX_LEN];
    uint16_t len;
    bool ready;
    bool valid;
} UART2_RxPacket_t;

// --- 新增：解析后的数据结构体 ---
typedef struct {
    char cmd;        // 指令字符，如 'S' 或 'D'
    int32_t param1;      // 第一个参数 (如 500 或 1200)
    int32_t param2;      // 第二个参数 (如 200)
    bool updated;    // 数据更新标志，解析成功后置 true
} UART2_ParsedData_t;

// 声明外部变量
extern volatile UART2_RxPacket_t g_uart2Rx;
extern volatile UART2_ParsedData_t g_uartParsed; // 新增：解析后的全局变量

// 函数声明
void UartSendChar(UART_Regs *uart, const uint8_t chr);
void UartSendString(UART_Regs *uart, const char *str);
void UartProcess(void); // 新增：串口处理函数声明

#endif
