#pragma once
#include "main.h"
#include "bgt60.h"

#define BGT60_SPI_TIMEOUT 100

void bgt60_stm32_setSPI(SPI_HandleTypeDef *SPI, GPIO_TypeDef *CS_port, uint16_t CS_pin);

bgt60_err_t bgt60_stm32_transceive(uint32_t n, uint8_t *tx_buf, uint8_t *rx_buf);
bgt60_err_t bgt60_stm32_read_reg(uint8_t reg_adr, uint32_t n, uint8_t *buf);
bgt60_err_t bgt60_stm32_write_reg(uint8_t reg_adr, uint32_t n, const uint8_t *buf);
bgt60_err_t bgt60_stm32_gpio_cs_en(int enable);