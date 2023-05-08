/*
 * my_util.c
 *
 *  Created on: May 8, 2023
 *      Author: marcsekz
 */

#include "my_util.h"

static TIM_HandleTypeDef *m_timer;

void Delay_us_Init(TIM_HandleTypeDef *timer_handle)
{
    m_timer = timer_handle;
}

void Delay_us(uint16_t delay)
{
    __HAL_TIM_SET_COUNTER(m_timer, 0); // Start timer from 0
    while (__HAL_TIM_GET_COUNTER(m_timer) < delay)
        ;
}