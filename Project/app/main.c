/**
		Filename: main.c
		Description: Main Program for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "drivers.h"
#include "CLI.h"
#include "app.h"
#include "drivers.h"
#include "timer.h"
#include "pwm.h"
#include "time_opps.h"
#include "time_trig_ops.h"

// Timing parameters
uint16_t last_time = 0; // previous ADC read time
uint16_t curr_time = 0; // current ADC read time
_Bool dont_sleep = 1; 	// no sleep

/* state machine states */
typedef enum {
    BEGIN,
    READ_ADC,
		CALCULATE_CONTROL_SIGNAL,
    UPDATE_SERVO_POSITION
} state;

float error, prev_error, control_signal = 0.0; // control errors and control_signal (effort)
uint16_t sample;

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
		if (control_flag)
		{
			curr_time = get_count(); // get timer count
			
			if ((curr_time - last_time == 800) || 
					(10000 - last_time + curr_time) == 800 ||
					dont_sleep){ 
			
					// Switch statement handdling state machine transitions
					switch(current_state){
						case BEGIN:
							
							current_state = READ_ADC; 			// switch states
							dont_sleep = 1;									// don't sleep till next state
							break;
						
						case READ_ADC:
							last_time = curr_time; 					// update previous reading time
							sample = get_height(); // read the height of the ball
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
			}
		// Tend to command if "/r" is received
		if (cmd_received_flag) {
        cmd_received_flag = 0;
        handle_CLI();
    }
	}
}
