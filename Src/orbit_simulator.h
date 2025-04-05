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
 * @file    airport_train.h
 * @brief   h file for airport_train.c
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */
#ifndef ORBIT_SIMULATOR_H
#define ORBIT_SIMULATOR_H

#include <stdbool.h>
#include "switch.h"
#include "led.h"
#include "log.h"
#include "systick_timer.h"

#define BRIGHTNESS_AT_T 0xFF
#define BRIGHTNESS_AT_A 0x87
#define BRIGHTNESS_AT_S 0x0F
#define LENGTH_OF_TRANSITION 4000
#define NUM_OF_BRIGHTNESS_CHANGES 8
#define MS_BETWEEN_BRIGHTNESS_CHANGES (LENGTH_OF_TRANSITION/NUM_OF_BRIGHTNESS_CHANGES)
#define ORBIT_START_DURATION 250

// Enum for positions (states)
enum burn_type
{
	PROGRADE,
	RETROGRADE
};

// Struct for holding the train's state
typedef struct
{
	enum position position;
	led leds[NUM_ORBIT_LEDS];
} orbit_state;

// Global state - init to start at pos ZERO
extern orbit_state cur_orbit_state;

void init_orbit_state();

void run_orbit_simulator();

void update_orbit_eccentricity(enum position position, enum burn_type burn);

#endif /* ORBIT_SIMULATOR_H */
