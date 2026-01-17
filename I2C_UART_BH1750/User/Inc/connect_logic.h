#ifndef _CONNECT_LOGIC
#define _CONNECT_LOGIC

#include "main.h"

#define TX_BUF_SIZE 32

char tx_buf[TX_BUF_SIZE];

void USART2_SendNumber(uint32_t num);
uint8_t u32_to_str(uint32_t val, char *buf);
void send_arr_usart2 (const char *buf, uint16_t len);

uint8_t I2C2_WriteByte(uint8_t addr, uint8_t data);

void USART2_logic(uint8_t *buf, uint16_t dSize, bool need_s);
void DMA_buf(uint8_t *bufAddr, uint16_t dSize, bool need_s);
enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value);
void send_string_usart2 (const char *buf);
#endif