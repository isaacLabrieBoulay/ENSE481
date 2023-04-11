/**
		Filename: app.c
		Description: This file defines all application functions for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-01-29
		Class: ense481
		Project: lab1
*/

#include "drivers.h"
#include "CLI.h"
#include "pwm.h"
#include "app.h"
#include "timer.h"
#include <stm32f10x.h>
#include <stdio.h>
#include <stdlib.h>

#define ANGLE_EQ    901 
#define ANGLE_LOW   ANGLE_EQ*(1-0.18)
#define ANGLE_HIGH  ANGLE_EQ*(1+0.18)
#define PID_MIN     -1000
#define PID_MAX     1000
#define PWM_MIN     0x258
#define PWM_MAX     0x5DC
#define ANGLE_MIN   0x258
#define ANGLE_MAX   0x5DC

// PID controller parameters
float Kp = 0.01;// Proportional gain
float Ki = 0.7; // Integral gain
float Kd = 4.5; // Derivative gain

void delay(uint32_t wait_time){
	uint32_t tick = 0;
	while(1){
		if (tick == wait_time)
			break;
		else
			tick++;
	}
}
uint16_t get_count(void){
	return TIM3_read();
}
uint16_t get_height(void){
	return read_ADC();
}
void blink_LED(){
	while(1){
		start_LED();
		delay(1600000);
		stop_LED();
		delay(1600000);
	}
}
void clear_buffers(uint8_t rx_buf[], uint8_t tx_buf[], uint8_t buffer_size){
	/* zero all indeces of Tx/Rx buffers */
	int i;
	for (i = 0; i < 50; i++){
		rx_buf[i] = 0x00;
		tx_buf[i] = 0x00;
	}
}
uint8_t read_character(uint8_t *pdata, uint8_t cursor){
	rx_USART(&pdata[cursor]);
	cursor++; // increment cursor
	return cursor;
}
uint8_t delete_character(uint8_t rx_buf[], uint8_t cursor){
	/* delete DEL and previous character */
	rx_buf[cursor-1] = 0x00;
	rx_buf[cursor-2] = 0x00;
	cursor = cursor - 2;
	return cursor;
}
void initial_boost(){
	write_dutycycle_PWM(0x258); // Start the ball at the bottom
	delay(8000000);
	write_dutycycle_PWM(0x450); // Give it a little bit of lift
	delay(8000000);
}
void send_message(uint8_t *pdata, uint8_t size){
	uint8_t buffer_index = 0;
	while(buffer_index < size){
		buffer_index++;// increment counter
		tx_USART(pdata);//transmit data at pdata
		pdata++;// increment pointer
	}
}
void update_servo_angle(float control_signal) {
	
		control_signal = control_signal*-1.0; //Invert control signal
		
		// Clip PID control signal to (-1000, 1000)
		if(control_signal < PID_MIN)
			control_signal = PID_MIN;
		else if (control_signal > PID_MAX)
      control_signal = PID_MAX;
  
		// map to output in PWM range (PWM_MIN, PWM_MAX)
    float angle_before_cast = (control_signal - PID_MIN) / (PID_MAX - PID_MIN) * (PWM_MAX - PWM_MIN) + PWM_MIN;
    
		// further clip the output angle to range (ANGLE_LOW, ANGLE_HIGH)
		if (angle_before_cast > ANGLE_HIGH)
			angle_before_cast = ANGLE_HIGH;
		else if(angle_before_cast < ANGLE_LOW)
			angle_before_cast = ANGLE_LOW;
		
		// cast the angle value to an unsigned integer for PWM
		uint16_t angle = (uint16_t)angle_before_cast;
		/*
		uint8_t out[] = "angle: ";
		send_message(out, sizeof(out));
		send_uint(angle);
		*/
		write_dutycycle_PWM(angle); // Write the PWM
}

float calculate_PID(float error, float prev_error){
	
	float proportional_term = Kp * error; 	 // calculate proportional term
	
	float integral = (error + prev_error)/2; // calculate 2 point triangle integral
	float integral_term = Ki * integral;		 // calculate integral term
	
	float derivative = error - prev_error; 	 // calculate derivative
	float derivative_term = Kd * derivative; // calculate the derivative term
	
	/* add them all up to get the control signal */
	float control_signal = proportional_term + integral_term + derivative_term;
	
	/** TROUBLESHOOTING **/
	/*
	uint8_t message1[] = "error: ";
	send_message(message1, sizeof(message1));
	send_float(error);
	uint8_t message2[] = "prev_error: ";
	send_message(message2, sizeof(message2));
	send_float(prev_error);
	uint8_t message3[] = "proportional_term: ";
	send_message(message3, sizeof(message3));
	send_float(proportional);
	uint8_t message4[] = "integral_term: ";
	send_message(message4, sizeof(message4));
	send_float(integral_term);
	uint8_t message5[] = "derivative_term: ";
	send_message(message5, sizeof(message5));
	send_float(derivative_term);
	uint8_t message6[] = "control_signal: ";
	send_message(message6, sizeof(message6));
	send_float(control_signal);
	*/
	return control_signal;
}
