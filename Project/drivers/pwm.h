/**
		Filename: pwm.h
		Description: This file declares PWM functions for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#ifndef PWM_H
#define PWM_H

#include <stm32f10x.h>
#include <stdint.h>

#define MIN_ANGLE 0 // minimum angle in degrees
#define MAX_ANGLE 180 // maximum angle in degrees
#define ANGLE_RANGE (MAX_ANGLE - MIN_ANGLE) // angle range in degrees
#define PWM_MIN     0x04B0
#define PWM_MAX     0x0834
#define DUTY_CYCLE_RANGE 1800 // duty cycle range in us

/** Initialize PWM hardware using TIM4 */
void start_PWM (void);

/** Update PWM based on CLI angle */
void write_angle_PWM (uint16_t);

/** Update PWM  */
void write_dutycycle_PWM(uint16_t);

#endif
