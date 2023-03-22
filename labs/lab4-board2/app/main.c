/**
Filename: main.c
10
Description: Main Program for CLI utility
Author: Isaac Labrie-Boulay (200391860)
Date: 2023-02-07
Class: ense481
Project: lab1 (USART)
*/
#include "drivers.h"
#include "CLI.h"
#include <stdint.h>
#include "app.h"
#include "drivers.h"
#include "timer.h"
#include "pwm.h"
#include <stdio.h>
#include <math.h>
#include "time_opps.h"
#include "time_trig_ops.h"
#define  M_PI  3.14159265358
#define cos_30 sqrt(3)/2
#define sin_30 1/2

uint8_t buffer_size = 40; // max amount of characters in tx/rx buffers
uint8_t cursor = 0; // cursor initially at 0

int main(){ 
	
	start_PWM();

	//while (1) {}                                     // Loop forever
	
	/* Initialize Buffers */
	uint8_t rx_buffer_CLI[buffer_size];
	uint8_t tx_buffer_CLI[buffer_size];
	
	/* Set GPIOA for LD2 */
	open_portA();
	open_LED();
	
	/* Setup USART2 (PA2 = Tx, PA3 = Rx) */
	reset_USART();
	open_USART();
	
	delay(5000); // for good measure
	
	timer_init();
	
	init_message_CLI();
	
	open_ADC();  // open and start ADC
	start_ADC();
	
	/** ADC TEST **/
	while(1){
		uint16_t data = read_ADC();
		print_voltage(data);
		delay(500000);
	}
	
	/* Start of CLI program */
	while(1){
		
		
		if(rx_ready_USART()){ // Continuously polling for data in USART2 data register
			
			/* get character. *Note: Both send_character() and delete_character() update the cursor position */
			cursor = read_character(rx_buffer_CLI, cursor);

			/* Everytime a character is sent, we send it back for visual feedback */
			tx_buffer_CLI[0] = rx_buffer_CLI[cursor-1];
			tx_USART(tx_buffer_CLI);
			
			/* verify command if an 'enter' is found */
			if(rx_buffer_CLI[cursor-1] == '\r'){
				
				/* identify command*/
				uint8_t action = parser_CLI(rx_buffer_CLI);
				
				/* For every command, clear buffers and transmit a 'return' */
				cursor = carriage_return_CLI(rx_buffer_CLI,tx_buffer_CLI, buffer_size, cursor);
				
				/* Execute action based on command */
				switch(action){
					case 0: // help
						help_CLI();
						break;
					case 1: // turn on LED
						start_LED();
						break;	
					case 2: // turn off LED
						stop_LED();	
						break;
					case 3: // query LED
						break;
					case 4: // date & time
						date_and_time_CLI();
						break;
					case 5: // timer script
						timer_CLI(); // print out times
						break;
					default:
						help_CLI(); // defaults to the help command
						break;
				}
			}
			/* Handles DEL */
			if(rx_buffer_CLI[cursor-1] == 0x7F){
				cursor = delete_character(rx_buffer_CLI, cursor);
			}
		}
	}
}
