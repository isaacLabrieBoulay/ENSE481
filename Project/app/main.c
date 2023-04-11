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

#define BUFFER_SIZE 40 // max amount of characters in tx/rx buffers

/* Initialize Buffers */
uint8_t rx_buffer_CLI[BUFFER_SIZE];
uint8_t tx_buffer_CLI[BUFFER_SIZE];
uint8_t cursor = 0; // cursor initially at 0

// Initial voltage setpoint
int16_t setpoint = 1700;

// Timing parameters
uint16_t last_time = 0;
uint16_t curr_time = 0;
_Bool dont_sleep = 1;

/* state machine states */
typedef enum {
    BEGIN,
    READ_ADC,
		CALCULATE_CONTROL_SIGNAL,
    UPDATE_SERVO_POSITION
} state;

float error, prev_error, control_signal = 0.0; // control errors and control_signal (effort)

int main(){ 
	
	start_PWM();   							 // Start PWM
	open_portA();  							 // Configure GPIO for LED
	open_LED();									 // Turn on LED
	reset_USART(); 							 // Restart USART
	open_USART();
	open_ADC();  	 							 // Open and start ADC
	start_ADC();
	TIM2_init();	 							 // start timer 2
	TIM3_init();	 							 // start timer 3
	init_message_CLI(); 				 // Display initial message
	
	state current_state = BEGIN; // give program its initial state

	/* Start the program */
	while(1){
		
		/* Sampling at 12.5 Hz 
		Few Notes: 
				- timer increment every 0.1ms
					therefore, need to take a sample once timer increments by 0.1ms*800=80ms
		
				- the state machine does not sleep when:
					i)   transitionning from BEGIN to READ_ADC
					ii)  transitionning from READ_ADC to CALCULATE_CONTROL_SIGNAL
					iii) transitionning from CALCULATE_CONTROL_SIGNAL to UPDATE_SERVO_POSITION
				
				- It only sleeps waiting for curr_time-last_time == 80ms after updating the servo
		**/
		
		curr_time = get_count(); // get timer count
		
		if ((curr_time - last_time == 800) || 
				(10000 - last_time + curr_time) == 800 ||
				dont_sleep){ 
		
				/** Switch statement handdling state machine transitions */
				switch(current_state){
					case BEGIN:
						initial_boost(); 					// Initially, reset the ball position and give it a boost
						
						current_state = READ_ADC; // switch states
						dont_sleep = 1;						// don't sleep till next state
						break;
					
					case READ_ADC:
						last_time = curr_time; 					// update previous reading time
						uint16_t sample = get_height(); // read the height of the ball
						prev_error = error;							// update the previous error value
						error = setpoint - sample;			// calculate the current error based on setpoint
						
						current_state = CALCULATE_CONTROL_SIGNAL; // switch states
						dont_sleep = 1;														// don't sleep till next state
						break;
					
					case CALCULATE_CONTROL_SIGNAL:
						
						control_signal = calculate_PID(error, prev_error); // Calculate control signal
						
						current_state = UPDATE_SERVO_POSITION; // switch states
						dont_sleep = 1;												 // don't sleep till next state
						break;
					
					case UPDATE_SERVO_POSITION:
						
						update_servo_angle(control_signal); // Map control signal to PWM output			
						
						dont_sleep = 0; // Sleep till next sample
						current_state = READ_ADC;
						break;
				}
			}
			
/*
		if(rx_ready_USART()){ // Continuously polling for data in USART2 data register
			
			// get character. *Note: Both send_character() and delete_character() update the cursor position 
			cursor = read_character(rx_buffer_CLI, cursor);

			// Everytime a character is sent, we send it back for visual feedback 
			tx_buffer_CLI[0] = rx_buffer_CLI[cursor-1];
			tx_USART(tx_buffer_CLI);
			
			//verify command if an 'enter' is found
			if(rx_buffer_CLI[cursor-1] == '\r'){
				
				
				uint8_t action = parser_CLI(rx_buffer_CLI);
				
				cursor = carriage_return_CLI(rx_buffer_CLI,tx_buffer_CLI, BUFFER_SIZE, cursor);
				
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
			// Handles DEL
			if(rx_buffer_CLI[cursor-1] == 0x7F){
				cursor = delete_character(rx_buffer_CLI, cursor);
			}
		
		}*/
	}
}
