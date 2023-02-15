/**
		Filename: CLI.h
		Description: This file declares all CLI functions for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-01-29
		Class: ense481
		Project: lab1
*/

#ifndef DRIVERS_H
#define DRIVERS_H
#include <stdint.h>
#include <stm32f10x.h>
#include "drivers.h"
#include "app.h"

/** Greet user on startup */
void init_message_CLI(void);

/** Parse command and identify action 

		Parameter(s)
			comm: uint8_t*, received data
			
		returns
			action: unsigned integer code for an action
	*/
uint8_t parser_CLI(uint8_t*);

/** send help to user */
void help_CLI(void);

/** Display a change line 

		Parameter(s)
			rx_buf[]: uint8_t*
			tx_buf[]: uint8_t*
			size: size of the buffers
			cursor: current position of the cursor
			
		returns
			cursor: updated position of cursor (cursor = 0)
	*/
uint8_t carriage_return_CLI(uint8_t*, uint8_t*, uint8_t, uint8_t);

/** Display the time and data */
void date_and_time_CLI(void);
#endif
