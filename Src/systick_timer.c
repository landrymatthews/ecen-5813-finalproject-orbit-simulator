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
 * @file    systick_timer.c
 * @brief  	Functions that use systick to help coordinate timing of actions in the train system
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */

#include "systick_timer.h"
#include "switch.h"
#include "orbit_simulator.h"

// Timer counter that tracks number of ms that have elapsed since boot. Updated by SysTick_Handler
static ticktime_t g_timer_count = 0;

/*
 * Initialize the timing system
 */
void init_systick()
{
	// Set reload field to get .01 sec interrupts.
	MODIFY_FIELD(SysTick->LOAD, SysTick_LOAD_RELOAD, CYCLES_PER_INTERRUPT-1);
	NVIC_SetPriority(SysTick_IRQn, 3); // Setting priority
	MODIFY_FIELD(SysTick->VAL, SysTick_VAL_CURRENT, 0); // Force reload of value

	// Enable interrupt, enable SysTick timer (start counting)
	// This also enables the Ext 6 Mhz clock
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/*
 * Get the current time since the timer started in ms
 */
ticktime_t now()
{
	return g_timer_count;
}

/*
 * Increments the global timer_count used for timekeeping
 */
__attribute__ ((optimize("O0")))
void SysTick_Handler(void)
{
	g_timer_count++;
	// IF g_Time_count % 250 == 0
		// update earth brightness
	if (was_pressed_once)
	{
		if (now() - press_start_time >= DOUBLE_PRESS_THRESHOLD)
		{

	    	update_orbit_eccentricity(cur_orbit_state.position, PROGRADE);
		}
	}
}

