/**
		Filename: timer.h
		Description: This file declares all timer drivers
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-15
		Class: ense481
		Project: lab2
*/

#ifndef TIMER_H
#define TIMER_H
#include <stm32f10x.h>
#include <stdint.h>

/** Initialize TIM2 as a continuous, free-running
		countdown timer


	*/
void timer_init(void);

/** Start Timer

		returns 
			Current value of the timer (16-bit signed int)
	*/
int16_t timer_start(void);

/** Stops timer and calculate time difference

		Parameter(s)
			start_time (int16_t): checks time since start_time
			
		returns 
			Difference between current time and start_time
	*/
int16_t timer_stop(uint16_t start_time);

/** Unitialize TIM2 (undoes timer_init) */
void timer_shutdown(void);
#endif
