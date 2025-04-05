/*******************************************************************************
 * Copyright (C) 2025 by Landry Matthews
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Landry Matthews and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    switch.h
 * @brief   h file for switch.c
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */
#ifndef SWITCH_H
#define SWITCH_H

#include <stdbool.h>
#include "stm32f091xc.h"
#include "utilities.h"

#define SWITCH_GPIO_PORT GPIOC
#define SWITCH_PIN 13
#define SWITCH_IDR SWITCH_GPIO_PORT->IDR
#define SWITCH_PIN_MASK GPIO_IDR_13
#define GPIO_PULL_UP_VALUE 1
#define MASK(x) (1UL << (x))
#define CLEAR_PENDING_REQUESTS 0x0000FFF0
#define PRIORITY_LEVEL 3
#define EXTICR_INDEX 3
#define SYSCFG_EXTICR4_EXTI13_VALUE 2


#define DOUBLE_PRESS_THRESHOLD 250
extern bool was_pressed_once = false;     // Flag for double press
extern ticktime_t press_start_time = 0;    // Start time for detecting press duration

void init_switch();

bool get_emergency_button_state();

#endif /* SWITCH_H */
