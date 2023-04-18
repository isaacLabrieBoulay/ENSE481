/**
		Filename: app.h
		Description: This file declares all application function for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#ifndef APP_H
#define APP_H

#include <stm32f10x.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"
#include "drivers.h"
#include "CLI.h"
#include "pwm.h"
#include "timer.h"

#define ANGLE_EQ    0x0668
#define ANGLE_LOW   ANGLE_EQ*(1-0.06)
#define ANGLE_HIGH  ANGLE_EQ*(1+0.06)
#define PID_MIN     -1000
#define PID_MAX     1000

#define LOOKUP_TABLE_SIZE 10

extern int16_t setpoint;

typedef struct {
    int height;
    uint16_t adc;
} LUT;

// height LUT for setting setpoints
extern LUT height_lut[LOOKUP_TABLE_SIZE];

// This global flag delineates closed/open loop control of the ball height
extern volatile _Bool control_flag;

/** Helper function facilitating a delay 

		Parameter(s)
			wait_time: unsigned integer representing wait time
	*/
void delay(uint32_t wait_time);

/** Simply read the value of the time counter */
uint16_t get_count(void);

/** Return the height of the ball (0-4095) */
uint16_t get_height(void);

/** Blink LED */
void blink_LED(void);

/** Read one character 

		Parameter(s)
			pdata: uint8_t*, buffer
			cursor: uint8_t current buffer cursor position
			
		returns
			cursor: updated position of cursor (+1)
	*/
uint8_t read_character(uint8_t*, uint8_t);

/** Delete One character 

		Parameter(s)
			rx_buf[]: uint8_t*, buffer
			cursor: uint8_t current buffer cursor position
			
		returns
			cursor: updated position of cursor (-2)
	*/
uint8_t delete_character(uint8_t*, uint8_t);

/** Turn CLI height from rx_buffer into unint16 setpoint

		Parameter (s)
			None
		
		returns
			height: uint16_t, value between 0-4095 for setpoint
*/
uint16_t parse_height(void);

/** initial_boost - lift ball halfway up the tube */
void initial_boost(void);
/** Transmit a whole string serially

		Parameter(s)
			message: uint8_t*, pointer to the message
			size: uint8_t size of string
	*/
void send_message(uint8_t*, uint8_t);

/** Maps control signal to output range (0 deg to 90 deg)

		Paramter (s)
			value: The computed control signal
			
		returns
			PWM value proportional to control signal

 */
void update_servo_angle(float);

/** Calculate control signal for PID controller based on errors

		Paramter (s)
			error: float, current control error relative to setpoint
			prev_error: float, last readings error relative to setpoint
			
		returns
			control signal: float, control effort

*/
float calculate_PID(float, float);


#endif



