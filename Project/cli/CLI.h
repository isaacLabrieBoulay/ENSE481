/**
		Filename: CLI.h
		Description: This file declares all CLI functions for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#ifndef CLI_H
#define CLI_H

#include <stdint.h>
#include <stm32f10x.h>
#include <string.h>
#include "drivers.h"
#include "app.h"
#include "pwm.h"
#include "drivers.h"
#include "timer.h"
#include "time_trig_ops.h"
#include "time_opps.h"

/** Greet user on startup */
void init_message_CLI(void);

/** Perform system function based on CLI command (parser_CLI) */
void handle_CLI(void);

/** Parse command and identify action from rx_buffer

		returns
			action: uint8_t, 
				0: 'help'
				1: 'date & time'
				2: 'function timer routine'
				3: 'change angle'
				4: 'disable closed loop'
				5: 'enable closed loop'
				6: 'set ball height'				
*/
uint8_t parser_CLI(void);

/** send help to user */
void help_CLI(void);

/** clear both buffers 

		Parameter(s)
			rx_buf: uint8_t*, pointer to the message
			tx_buf: uint8_t size of string
			size: uint8_t size of the buffers
	*/
void clear_buffers(void);

/** Display a change line 

		Parameter(s)
			rx_buf[]: uint8_t*
			tx_buf[]: uint8_t*
			size: size of the buffers
			cursor: current position of the cursor
			
		returns
			cursor: updated position of cursor (cursor = 0)
	*/
uint8_t carriage_return_CLI(void);

/** Display the time and data */
void date_and_time_CLI(void);

/** Script finding the average runtime of each operation */
void timer_CLI(void);

/** utility function to send an integer by USART */
void send_uint(uint16_t);

/** utility function to send a float by USART */
void send_float(float);

/** utility function to send the time by USART */
void send_time(uint16_t);

/** utility function to parse angle from the command line */
uint16_t parse_angle(void);

/** Prints out an ADC reading in terms of voltage */
void print_voltage(uint16_t adc_val);

#endif
