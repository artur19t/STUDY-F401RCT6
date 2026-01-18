#ifndef _CONNECT_LOGIC
#define _CONNECT_LOGIC

#include "main.h"

#define TX_BUF_SIZE 32

#define BH1750_ADDR_GND   (0x23 << 1)
#define BH1750_CMD_POWER_ON  0x01
#define BH1750_CMD_RESET     0x07
#define BH1750_CMD_CONT_H    0x10

char tx_buf[TX_BUF_SIZE];

void USART2_SendNumber(uint32_t num);
uint8_t u32_to_str(uint32_t val, char *buf);
void send_arr_usart2 (const char *buf, uint16_t len);

uint16_t I2C_Read2Bytes(uint8_t address);
uint8_t I2C2_WriteByte(uint8_t addr, uint8_t data);
void BH1750_Init(void);

void USART2_logic(uint8_t *buf, uint16_t dSize, bool need_s);
void DMA_buf(uint8_t *bufAddr, uint16_t dSize, bool need_s);
enum parse_status_t parse_from_uart(const uint8_t *buf, uint16_t len, uint32_t *value);
void send_string_usart2 (const char *buf);
#endif