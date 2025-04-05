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
 * @file    systick_timer.h
 * @brief   h file for systick_timer.c
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */

#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include "utilities.h"
#include "stm32f091xc.h" // Includes core_cm0plus.h

// Timings
#define F_SYS_CLK (48000000L)
#define E_SYS_CLK (F_SYS_CLK/8)
#define SYSTICK_INTERRUPTS_PER_SECOND 1000 // Easy to just define this as milliseconds
#define CYCLES_PER_INTERRUPT (E_SYS_CLK/SYSTICK_INTERRUPTS_PER_SECOND)

// type for dealing with timing clock cycles
typedef uint32_t ticktime_t;

void init_systick();

ticktime_t now();

#endif /* SYSTICK_TIMER_H */

