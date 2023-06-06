#include "bgt60_stm32.h"

SPI_HandleTypeDef *m_spi = NULL;
GPIO_TypeDef *m_cs_port;
uint16_t m_cs_pin;

static inline bgt60_err_t bgt60_errorconv(HAL_StatusTypeDef err)
{
    // More detailed implementation:
    // switch (err)
    // {
    // case HAL_OK:
    //     return E_BGT60_SUCCESS;
    // case HAL_ERROR:
    //     return E_BGT60_ERR;
    // case HAL_BUSY:
    // case HAL_TIMEOUT:
    //     return E_BGT60_COM_ERR;
    // }

    // Simple implementation:
    if (err == HAL_OK)
        return E_BGT60_SUCCESS;
    return E_BGT60_COM_ERR;
}

void bgt60_stm32_setSPI(SPI_HandleTypeDef *SPI, GPIO_TypeDef *CS_port, uint16_t CS_pin)
{
    m_spi = SPI;
    m_cs_port = CS_port;
    m_cs_pin = CS_pin;
}

bgt60_err_t bgt60_stm32_transceive(uint32_t n, uint8_t *tx_buf, uint8_t *rx_buf)
{
    return bgt60_errorconv(HAL_SPI_TransmitReceive(m_spi, tx_buf, rx_buf, n, BGT60_SPI_TIMEOUT));
}

bgt60_err_t bgt60_stm32_read_reg(uint8_t reg_adr, uint32_t n, uint8_t *buf)
{
    HAL_StatusTypeDef ret;

    WRITE_REG(m_spi->Instance->CFG1, SPI_DATASIZE_24BIT);
    ret = HAL_SPI_Receive(m_spi, buf, n, BGT60_SPI_TIMEOUT);
    WRITE_REG(m_spi->Instance->CFG1, SPI_DATASIZE_32BIT);
    return bgt60_errorconv(ret);
}

bgt60_err_t bgt60_stm32_write_reg(uint8_t reg_adr, uint32_t n, const uint8_t *buf)
{
    HAL_StatusTypeDef ret;

    WRITE_REG(m_spi->Instance->CFG1, SPI_DATASIZE_24BIT);
    ret = HAL_SPI_Transmit(m_spi, buf, n, BGT60_SPI_TIMEOUT);
    WRITE_REG(m_spi->Instance->CFG1, SPI_DATASIZE_32BIT);
    return bgt60_errorconv(ret);
}

bgt60_err_t bgt60_stm32_gpio_cs_en(int enable)
{
    HAL_GPIO_WritePin(m_cs_port, m_cs_pin, enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
    return E_BGT60_SUCCESS;
}