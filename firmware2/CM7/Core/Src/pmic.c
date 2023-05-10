/*
 * pmic.c
 *
 *  Created on: May 5, 2023
 *      Author: marcsekz
 */

#include "pmic.h"

const uint8_t pmic_addr = 0x08;

const uint8_t burst_count = 5;

/// @brief Time of each initializer packet from reset
const uint8_t burst_time_ms[] =
    {15, 30, 42, 53, 133};

/// @brief Number of transactions in initializer packets
const uint8_t burst_size[] =
    {6, 2, 1, 3, 1};

/// @brief PMIC initializer I2C packets, from logic analyzer
const uint8_t burst_data[][2] =
    {
        {0x4f, 0x00},
        {0x50, 0x0f},
        {0x4c, 0x05},
        {0x4d, 0x03},
        {0x52, 0x09},
        {0x53, 0x0f},

        {0x9c, 0x80},
        {0x9e, 0x20},

        {0x42, 0x02},

        {0x94, 0xa0},
        {0x3b, 0x0f},
        {0x35, 0x0f},

        {0x42, 0x01}
     };

void PMIC_Init(I2C_HandleTypeDef *i2c)
{
    uint8_t tr_no = 0;
    uint32_t start = 0;  //HAL_GetTick();
    HAL_StatusTypeDef ret;
    for (uint8_t burst_no = 0; burst_no < burst_count; burst_no++)
    {
        while (HAL_GetTick() - start < burst_time_ms[burst_no])
        {
            HAL_Delay(1);
        }

        for (uint8_t i = 0; i < burst_size[burst_no]; i++)
        {
            ret = HAL_I2C_Master_Transmit(i2c, pmic_addr, burst_data[tr_no++], 2, 100);
        }
    }
}
