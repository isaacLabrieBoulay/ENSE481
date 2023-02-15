/**
		Filename: app.h
		Description: This file declares all application function for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-01-29
		Class: ense481
		Project: lab1
*/

#ifndef APP_H
#define APP_H
#include <stm32f10x.h>
#include <stdint.h>

/** Helper function facilitating a delay 

		Parameter(s)
			wait_time: unsigned integer representing wait time
	*/
void delay(uint32_t wait_time);

/** Blink LED */
void blink_LED(void);

/** clear both buffers 

		Parameter(s)
			rx_buf: uint8_t*, pointer to the message
			tx_buf: uint8_t size of string
			size: uint8_t size of the buffers
	*/
void clear_buffers(uint8_t[], uint8_t[], uint8_t);

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

/** Transmit a whole string serially

		Parameter(s)
			message: uint8_t*, pointer to the message
			size: uint8_t size of string
	*/
void send_message(uint8_t*, uint8_t);


#endif



