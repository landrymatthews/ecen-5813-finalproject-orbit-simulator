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
 * @file    switch.c
 * @brief   Implementation of functions that use the on board user switch for interrupts
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */

#include "switch.h"
#include "systick_timer.h"
#include "orbit_simulator.h"

// Variable to track switch interrupt - updated by EXTI4_15_IRQHandler


/*
 * Returns the state of the switch: true if closed/pressed
 */
//bool get_emergency_button_state()
//{
//	return g_switch_pressed;
//}

/*
 * Initialize our switch input with interrupts
 */
void init_switch(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	MODIFY_FIELD(SWITCH_GPIO_PORT->MODER, GPIO_MODER_MODER13,
			ESF_GPIO_MODER_INPUT);
	MODIFY_FIELD(SWITCH_GPIO_PORT->PUPDR, GPIO_PUPDR_PUPDR13,
			GPIO_PULL_UP_VALUE);
	// Enable peripheral clock for SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

	// Switch is at Port C bit 13
	MODIFY_FIELD(SYSCFG->EXTICR[EXTICR_INDEX], SYSCFG_EXTICR4_EXTI13,
			SYSCFG_EXTICR4_EXTI13_VALUE);

	// Set mask bits for inputs in EXTI_IMR
	EXTI->IMR |= MASK(SWITCH_PIN);
	// Trigger on both rising and falling edges in EXTI_RTSR and EXTI_FTSR
	EXTI->RTSR |= MASK(SWITCH_PIN);
//	EXTI->FTSR |= MASK(SWITCH_PIN);

	// Configure enable and mask bits for NVIC IRQ Channel for EXTI
	// Interrupt line 13 is serviced by EXTI4_15_IRQ
	NVIC_SetPriority(EXTI4_15_IRQn, PRIORITY_LEVEL);
	NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	__enable_irq();
}

/*
 * Interrupt handler for our switch. Sets g_switch_pressed for functions that use it
 */
void EXTI4_15_IRQHandler(void)
{
    // Clear all other pending requests for this handler
    EXTI->PR = CLEAR_PENDING_REQUESTS;


    if (was_pressed_once) {
    	// Double press
    	update_orbit_eccentricity(cur_orbit_state.position, RETROGRADE);

    }
    else
    {
    	was_pressed_once = true;
    	press_start_time = now();
    }
//    // Check if the button was pressed (active low)
//    if (~SWITCH_IDR & SWITCH_PIN_MASK)
//    {
//        uint32_t current_time = elapsed_time;  // Get the current elapsed time (in ms)
//
//        // First press or reset press timeout
//        if (last_press_time == 0 || current_time - last_press_time > press_timeout)
//        {
//            // This is the first press or a long delay between presses (single press)
//            g_switch_pressed = true;
//            is_double_press = false;  // Clear double press flag
//            press_start_time = current_time;  // Track when the press starts
//
//            // Wait for possible second press
//            last_press_time = current_time;
//        }
//        else if (current_time - last_press_time <= press_timeout)
//        {
//            // If the time difference is within the threshold, it's a double press
//
//            last_press_time = current_time;  // Update last press time
//        }
//    }
//    else
//    {
//        // Button is released, reset the flag
//        g_switch_pressed = false;
//    }
}
