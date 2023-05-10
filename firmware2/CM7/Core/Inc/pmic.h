/*
 * pmic.h
 *
 *  Created on: May 5, 2023
 *      Author: marcsekz
 */

#pragma once

#include "main.h"

/// @brief Initialize PMIC with default settings
/// @param i2c I2C handle to which PMIC is connected
void PMIC_Init(I2C_HandleTypeDef *i2c);
