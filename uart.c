#include "uart.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static uint16_t rx_idx = 0;
// 移除未使用的 receiving 变量

volatile UART2_RxPacket_t g_uart2Rx = {0};
volatile UART2_ParsedData_t g_uartParsed = {0};

void UartSendChar(UART_Regs *uart, const uint8_t chr) {
    DL_UART_transmitDataBlocking(uart, chr);
}

void UartSendString(UART_Regs *uart, const char *str) {
    while(*str) {
        UartSendChar(uart, (uint8_t)*str);
        str++;
    }
}

void UART2_INST_IRQHandler(void) {
    if (DL_UART_getPendingInterrupt(UART2_INST) == DL_UART_IIDX_RX) {
        DL_GPIO_togglePins(MOTOR_LED_PORT, MOTOR_LED_PIN);
        uint8_t data = DL_UART_receiveData(UART2_INST);

        // [修复1]：如果上一包数据未处理完，丢弃新数据，防止覆盖
        if (g_uart2Rx.ready == true) {
            return; 
        }

        // [修复2]：缓冲区溢出保护，大于等于最大长度时停止接收
        if (rx_idx >= UART2_MAX_LEN) {
            // 可以选择标记错误，或者直接丢弃
            return; 
        }

        g_uart2Rx.buffer[rx_idx++] = data;

        if (data == '\n') {
            g_uart2Rx.len = rx_idx;
            if (g_uart2Rx.buffer[0] == '$') {
                g_uart2Rx.valid = true;
            } else {
                g_uart2Rx.valid = false;
            }
            g_uart2Rx.ready = true; // 标记数据就绪，等待主循环处理
            // 注意：这里不能清零 rx_idx，要等主循环处理完之后清零
            // 或者是：这里暂不清理，等主循环处理完手动清理 buffer
        }
    }
}

void UartProcess(void) {
    if (g_uart2Rx.ready == true) {
        // [修复3]：使用本地缓冲区解析，避免操作 volatile 变量
        char local_buf[UART2_MAX_LEN];
        uint16_t len = g_uart2Rx.len;
        
        // 安全拷贝，确保有字符串结束符
        if (len >= UART2_MAX_LEN) len = UART2_MAX_LEN - 1;
        memcpy(local_buf, (const char*)g_uart2Rx.buffer, len);
        local_buf[len] = '\0';

        // 回显原始数据
        // UartSendString(UART2_INST, local_buf);

        // 解析逻辑
        if (g_uart2Rx.valid && local_buf[0] == '$') {
            if (len > 2) { // 简单长度校验
                g_uartParsed.cmd = local_buf[1];
                
                // 在本地 buffer 上进行字符串操作是安全的
                char *separator = strchr(&local_buf[2], ',');
                if (separator != NULL) {
                    *separator = '\0'; // 截断字符串以便获取参数1
                    g_uartParsed.param1 = atoi(&local_buf[2]);
                    g_uartParsed.param2 = atoi(separator + 1);
                    g_uartParsed.updated = true; // 通知 main 更新
                }
            }
        }

        // [关键]：处理完毕后，重置状态，允许接收新数据
        g_uart2Rx.ready = false;
        g_uart2Rx.valid = false;
        rx_idx = 0; // 只有在这里清零才是安全的
        memset((void*)g_uart2Rx.buffer, 0, UART2_MAX_LEN); // 可选：清空缓冲区
    }
}
