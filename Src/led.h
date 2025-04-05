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
 * @file    led.h
 * @brief   h file for led.c
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */
#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include "utilities.h"
#include "stm32f091xc.h"
//#include "orbit_simulator.h"

#define NUM_ORBIT_LEDS 10

// Enum for positions (states)
enum position
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

// Struct for controlling the LEDs
typedef struct
{
	uint32_t duration;
	enum position position;
} led;

void init_earth_led();
void init_orbit_leds();
//void set_earth_led_pwm();
void set_next_orbit_led(uint8_t led_index);

#endif /* LED_H */
