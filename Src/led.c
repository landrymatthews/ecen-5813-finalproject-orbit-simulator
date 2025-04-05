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
 * @file    led.c
 * @brief   Implementation of functions that use the ULED or ELED
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */

#include "led.h"

#define LED0_OFF_MSK (GPIO_BSRR_BS_0)
#define LED0_ON_MSK (GPIO_BSRR_BR_0)
#define LED1_OFF_MSK (GPIO_BSRR_BS_1)
#define LED1_ON_MSK (GPIO_BSRR_BR_1)
#define LED2_OFF_MSK (GPIO_BSRR_BS_2)
#define LED2_ON_MSK (GPIO_BSRR_BR_2)
#define LED3_OFF_MSK (GPIO_BSRR_BS_3)
#define LED3_ON_MSK (GPIO_BSRR_BR_3)
#define LED4_OFF_MSK (GPIO_BSRR_BS_4)
#define LED4_ON_MSK (GPIO_BSRR_BR_4)
#define LED5_OFF_MSK (GPIO_BSRR_BS_5)
#define LED5_ON_MSK (GPIO_BSRR_BR_5)
#define LED6_OFF_MSK (GPIO_BSRR_BS_6)
#define LED6_ON_MSK (GPIO_BSRR_BR_6)
#define LED7_OFF_MSK (GPIO_BSRR_BS_7)
#define LED7_ON_MSK (GPIO_BSRR_BR_7)
#define LED8_OFF_MSK (GPIO_BSRR_BS_8)
#define LED8_ON_MSK (GPIO_BSRR_BR_8)
#define LED9_OFF_MSK (GPIO_BSRR_BS_9)
#define LED9_ON_MSK (GPIO_BSRR_BR_9)

// For PWM
#define F_TIM_CLOCK 48000000
#define PWM_FREQUENCY (500)
#define PWM_MAX_DUTY_VALUE ((F_TIM_CLOCK / (PWM_FREQUENCY * PWM_PRESCALER)) - 1)
#define PWM_PRESCALER (2)
#define MAX_BRIGHTNESS 0xFF
#define PWM_MODE 6

/*
 * Initialize the ELED on PA7 with PWM function since ELED will be controlled by PWM
 */
void init_earth_led(void)
{
	// Configure PA7 with alternate function 1: TIM3_CH2
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	MODIFY_FIELD(GPIOA->MODER, GPIO_MODER_MODER7, ESF_GPIO_MODER_ALT_FUNC);
	MODIFY_FIELD(GPIOA->AFR[0], GPIO_AFRL_AFRL7, 1);

	// Configure TIM3 counter and prescaler
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = PWM_PRESCALER - 1;
	TIM3->ARR = PWM_MAX_DUTY_VALUE;
	TIM3->CR1 = 0; // count up

	// Configure TIM3 channel 2
	TIM3->CCR2 = 1;								// Short on-time by default
	TIM3->CCER |= TIM_CCER_CC2P;	// active low polarity
	MODIFY_FIELD(TIM3->CCMR1, TIM_CCMR1_OC2M, PWM_MODE); // Select PWM mode
	TIM3->CCMR1 |= TIM_CCMR1_OC2PE;	 // Enable preload register
	TIM3->EGR |= TIM_EGR_UG;			// Generate update
	TIM3->CCER |= TIM_CCER_CC2E; // Enable channel output on OC2
	TIM3->BDTR |= TIM_BDTR_MOE;		// Enable main output

	TIM3->CR1 |= TIM_CR1_CEN;			// Enable timer
}


void init_orbit_leds()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER0, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER1, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER2, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER3, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER4, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER5, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER6, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER7, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER8, ESF_GPIO_MODER_OUTPUT);
	MODIFY_FIELD(GPIOB->MODER, GPIO_MODER_MODER9, ESF_GPIO_MODER_OUTPUT);
	GPIOB->BSRR |= LED0_OFF_MSK;
	GPIOB->BSRR |= LED1_OFF_MSK;
	GPIOB->BSRR |= LED2_OFF_MSK;
	GPIOB->BSRR |= LED3_OFF_MSK;
	GPIOB->BSRR |= LED4_OFF_MSK;
	GPIOB->BSRR |= LED5_OFF_MSK;
	GPIOB->BSRR |= LED6_OFF_MSK;
	GPIOB->BSRR |= LED7_OFF_MSK;
	GPIOB->BSRR |= LED8_OFF_MSK;
	GPIOB->BSRR |= LED9_OFF_MSK;
}


/*
 * Sets the ELED using PWM scaling
 */
//static void set_earth_led_pwm(uint8_t brightness)
//{
//	// Interpolate between min and max values
//	TIM3->CCR2 = ((PWM_MAX_DUTY_VALUE * brightness) / MAX_BRIGHTNESS);
//}

/*
 * Set an LED based on index and turn it on, turning the previous one off
 * Index 0 to 9 for ELEDs (PB0 to PB9)
 * Index for ULED is 10
 */
void set_next_orbit_led(uint8_t led_index)
{
	if (led_index < NUM_ORBIT_LEDS) {
	    if (led_index == 0) {
	    	GPIOB->BSRR |= LED9_OFF_MSK; // Turn off LED9
	        GPIOB->BSRR |= LED0_ON_MSK;  // Turn on LED0
	    } else if (led_index == 1) {
	        GPIOB->BSRR |= LED0_OFF_MSK; // Turn off LED0
	        GPIOB->BSRR |= LED1_ON_MSK;  // Turn on LED1
	    } else if (led_index == 2) {
	        GPIOB->BSRR |= LED1_OFF_MSK; // Turn off LED1
	        GPIOB->BSRR |= LED2_ON_MSK;  // Turn on LED2
	    } else if (led_index == 3) {
	        GPIOB->BSRR |= LED2_OFF_MSK; // Turn off LED2
	        GPIOB->BSRR |= LED3_ON_MSK;  // Turn on LED3
	    } else if (led_index == 4) {
	        GPIOB->BSRR |= LED3_OFF_MSK; // Turn off LED3
	        GPIOB->BSRR |= LED4_ON_MSK;  // Turn on LED4
	    } else if (led_index == 5) {
	        GPIOB->BSRR |= LED4_OFF_MSK; // Turn off LED4
	        GPIOB->BSRR |= LED5_ON_MSK;  // Turn on LED5
	    } else if (led_index == 6) {
	        GPIOB->BSRR |= LED5_OFF_MSK; // Turn off LED5
	        GPIOB->BSRR |= LED6_ON_MSK;  // Turn on LED6
	    } else if (led_index == 7) {
	        GPIOB->BSRR |= LED6_OFF_MSK; // Turn off LED6
	        GPIOB->BSRR |= LED7_ON_MSK;  // Turn on LED7
	    } else if (led_index == 8) {
	        GPIOB->BSRR |= LED7_OFF_MSK; // Turn off LED7
	        GPIOB->BSRR |= LED8_ON_MSK;  // Turn on LED8
	    } else if (led_index == 9) {
	        GPIOB->BSRR |= LED8_OFF_MSK; // Turn off LED8
	        GPIOB->BSRR |= LED9_ON_MSK;  // Turn on LED9
	    }
	}
}
