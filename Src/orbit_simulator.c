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
 * @file    orbit_simulator.c
 * @brief   Implementation of state machine that controls the state and
 * 			behavior of our airport train LEDs
 *
 *
 * @author  Landry Matthews
 * @date    04/05/2025
 *
 */

#include "orbit_simulator.h"
cur_orbit_state = {
    .position = ZERO,
    .leds = {
        [0 ... NUM_ORBIT_LEDS-1] = { .duration = ORBIT_START_DURATION, .position = 0 }  // Initialize all LEDs with duration 250 and position 0
    }
};
// Post-initialization loop to assign correct positions
void init_orbit_state() {
    for (int i = 0; i < NUM_ORBIT_LEDS; i++) {
        cur_orbit_state.leds[i].position = (enum position)i;
    }
}

/*
 * Handles the repeated blink sequence for each station.
 * Calls do_one_blink as many times as needed followed by a single do_one_pause.
 *
 * Can be interrupted at any time by the emergency button
 *
 * Parameters:
 * int num_blink_seq - number of blink sequences needed for current station
 */
static void time_cur_led()
{
	LOG("\nStarting Blink Sequence...\r\n");
	ticktime_t start_time_on = now();

	enum position cur_pos = cur_orbit_state.position;
	set_next_orbit_led(cur_pos);
	while (now() - start_time_on < cur_orbit_state.leds[cur_pos].duration)
	{
		;
	}

	return;
	LOG("Blink Sequence Finished.\r\n");
}


/*
 * Prints out DEBUG information about the current state
 */
static void debug_print_state()
{
    LOG("\nSTATE TRANSITION INFO\r\n");
    LOG("Time Elapsed: %lu ms\r\n", now());

    // Print the current position of the orbit
    LOG("Current Position: ");
    switch (cur_orbit_state.position)
    {
    case ZERO:
        LOG("Position 0\r\n");
        break;
    case ONE:
        LOG("Position 1\r\n");
        break;
    case TWO:
        LOG("Position 2\r\n");
        break;
    case THREE:
        LOG("Position 3\r\n");
        break;
    case FOUR:
        LOG("Position 4\r\n");
        break;
    case FIVE:
        LOG("Position 5\r\n");
        break;
    case SIX:
        LOG("Position 6\r\n");
        break;
    case SEVEN:
        LOG("Position 7\r\n");
        break;
    case EIGHT:
        LOG("Position 8\r\n");
        break;
    case NINE:
        LOG("Position 9\r\n");
        break;
    default:
        LOG("Unknown Position\r\n");
        break;
    }

    // Print the durations of all LEDs
    LOG("LED Durations: ");
    for (int i = 0; i < NUM_ORBIT_LEDS; i++)
    {
        LOG("LED %d Duration: %lu ms", i, cur_orbit_state.leds[i].duration);
        if (i < 9) // To avoid extra comma at the end
            LOG(", ");
    }
    LOG("\r\n");

    // Print current ELED Brightness
//    LOG("Current Earth Brightness: %d\r\n", cur_orbit_state.eled.brightness);
}

/*
 * Main state machine loop. Checks the trains states and calls the appropriate functions.
 */
void run_orbit_simulator()
{

	LOG("Starting Airport Train at Terminal...\r\n");
	LOG("Entering Main Loop...\r\n");
	while (1)
	{
		// Debug mode output
		debug_print_state();

		// Shine LED at current pos
		time_cur_led();

		cur_orbit_state.position = cur_orbit_state.position == NINE ? ZERO : cur_orbit_state.position+1;
		// After duration, increment pos
		// Handle state transitions
//		switch (cur_orbit_state.pos)
//		{
//		    case ZERO:
//		        blink_sequences(cur_orbit_state.leds[ZERO]);  // Use duration for ZERO
//		        cur_orbit_state.pos = ONE;  // Transition to next state
//		        break;
//
//		    case ONE:
//		        blink_sequences(cur_orbit_state.leds[ONE]);  // Use duration for ONE
//		        cur_orbit_state.pos = TWO;  // Transition to next state
//		        break;
//
//		    case TWO:
//		        blink_sequences(cur_orbit_state.leds[TWO]);  // Use duration for TWO
//		        cur_orbit_state.pos = THREE;  // Transition to next state
//		        break;
//
//		    case THREE:
//		        blink_sequences(cur_orbit_state.leds[THREE]);  // Use duration for THREE
//		        cur_orbit_state.pos = FOUR;  // Transition to next state
//		        break;
//
//		    case FOUR:
//		        blink_sequences(cur_orbit_state.leds[FOUR]);  // Use duration for FOUR
//		        cur_orbit_state.pos = FIVE;  // Transition to next state
//		        break;
//
//		    case FIVE:
//		        blink_sequences(cur_orbit_state.leds[FIVE]);  // Use duration for FIVE
//		        cur_orbit_state.pos = SIX;  // Transition to next state
//		        break;
//
//		    case SIX:
//		        blink_sequences(cur_orbit_state.leds[SIX]);  // Use duration for SIX
//		        cur_orbit_state.pos = SEVEN;  // Transition to next state
//		        break;
//
//		    case SEVEN:
//		        blink_sequences(cur_orbit_state.leds[SEVEN]);  // Use duration for SEVEN
//		        cur_orbit_state.pos = EIGHT;  // Transition to next state
//		        break;
//
//		    case EIGHT:
//		        blink_sequences(cur_orbit_state.leds[EIGHT]);  // Use duration for EIGHT
//		        cur_orbit_state.pos = NINE;  // Transition to next state
//		        break;
//
//		    case NINE:
//		        blink_sequences(cur_orbit_state.leds[NINE]);  // Use duration for NINE
//		        cur_orbit_state.pos = ZERO;  // Wrap around back to state ZERO
//		        break;
//
//		    default:
//		        // Optionally handle an invalid state (this should never happen if pos is always within 0-9)
//		        break;
//		}
	}
}
#define MAX_TRANSITION_TIME 500  // Maximum transition time (ms)
#define MIN_TRANSITION_TIME 50   // Minimum transition time (ms)
#define INCREMENT_ADJACENT 50    // Time change for adjacent LEDs (ms)
#define INCREMENT_DOUBLE_ADJACENT 25  // Time change for double adjacent LEDs (ms)
#define INCREMENT_OPPOSITE 75    // Time change for opposite LED (ms)

// This function updates the orbit's eccentricity and modifies the transition times of LEDs.
void update_orbit_eccentricity(enum position pos, enum burn_type burn) {
    // The index of the "opposite" LED based on the current position.
    int opposite_position = (pos + (NUM_ORBIT_LEDS/2)) % NUM_ORBIT_LEDS;

    // Adjust the transition times based on burn type (retrograde or prograde)
    if (burn == PROGRADE) {
        // Increase the transition time for the opposite LED and adjacent LEDs
        if (cur_orbit_state.leds[opposite_position].duration + INCREMENT_OPPOSITE <= MAX_TRANSITION_TIME) {
        	cur_orbit_state.leds[opposite_position].duration += INCREMENT_OPPOSITE;
        } else {
        	cur_orbit_state.leds[opposite_position].duration = MAX_TRANSITION_TIME;
        }

        // Increase time for adjacent LEDs (one step away)
        for (int i = 1; i <= 2; i++) {
            int adj_pos_1 = (opposite_position + i) % NUM_ORBIT_LEDS;
            int adj_pos_2 = (opposite_position - i + NUM_ORBIT_LEDS) % NUM_ORBIT_LEDS;

            if (cur_orbit_state.leds[adj_pos_1].duration + INCREMENT_ADJACENT <= MAX_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_1].duration += INCREMENT_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_1].duration = MAX_TRANSITION_TIME;
            }

            if (cur_orbit_state.leds[adj_pos_2].duration + INCREMENT_ADJACENT <= MAX_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_2].duration += INCREMENT_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_2].duration = MAX_TRANSITION_TIME;
            }
        }

        // Increase time for double adjacent LEDs (two steps away)
        for (int i = 3; i <= 4; i++) {
            int adj_pos_1 = (opposite_position + i) % NUM_ORBIT_LEDS;
            int adj_pos_2 = (opposite_position - i + NUM_ORBIT_LEDS) % NUM_ORBIT_LEDS;

            if (cur_orbit_state.leds[adj_pos_1].duration + INCREMENT_DOUBLE_ADJACENT <= MAX_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_1].duration += INCREMENT_DOUBLE_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_1].duration = MAX_TRANSITION_TIME;
            }

            if (cur_orbit_state.leds[adj_pos_2].duration + INCREMENT_DOUBLE_ADJACENT <= MAX_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_2].duration += INCREMENT_DOUBLE_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_2].duration = MAX_TRANSITION_TIME;
            }
        }

    } else if (burn == RETROGRADE) {
        // Decrease the transition time for the opposite LED and adjacent LEDs
        if (cur_orbit_state.leds[opposite_position].duration >= INCREMENT_OPPOSITE + MIN_TRANSITION_TIME) {
        	cur_orbit_state.leds[opposite_position].duration -= INCREMENT_OPPOSITE;
        } else {
        	cur_orbit_state.leds[opposite_position].duration = MIN_TRANSITION_TIME;
        }

        // Decrease time for adjacent LEDs (one step away)
        for (int i = 1; i <= 2; i++) {
            int adj_pos_1 = (opposite_position + i) % NUM_ORBIT_LEDS;
            int adj_pos_2 = (opposite_position - i + NUM_ORBIT_LEDS) % NUM_ORBIT_LEDS;

            if (cur_orbit_state.leds[adj_pos_1].duration >= INCREMENT_ADJACENT + MIN_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_1].duration -= INCREMENT_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_1].duration = MIN_TRANSITION_TIME;
            }

            if (cur_orbit_state.leds[adj_pos_2].duration >= INCREMENT_ADJACENT + MIN_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_2].duration -= INCREMENT_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_2].duration = MIN_TRANSITION_TIME;
            }
        }

        // Decrease time for double adjacent LEDs (two steps away)
        for (int i = 3; i <= 4; i++) {
            int adj_pos_1 = (opposite_position + i) % NUM_ORBIT_LEDS;
            int adj_pos_2 = (opposite_position - i + NUM_ORBIT_LEDS) % NUM_ORBIT_LEDS;

            if (cur_orbit_state.leds[adj_pos_1].duration >= INCREMENT_DOUBLE_ADJACENT + MIN_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_1].duration -= INCREMENT_DOUBLE_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_1].duration = MIN_TRANSITION_TIME;
            }

            if (cur_orbit_state.leds[adj_pos_2].duration >= INCREMENT_DOUBLE_ADJACENT + MIN_TRANSITION_TIME) {
            	cur_orbit_state.leds[adj_pos_2].duration -= INCREMENT_DOUBLE_ADJACENT;
            } else {
            	cur_orbit_state.leds[adj_pos_2].duration = MIN_TRANSITION_TIME;
            }
        }
    }
}
