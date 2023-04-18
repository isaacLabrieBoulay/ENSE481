/**
		Filename: app.c
		Description: This file defines all application functions for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#include "app.h"

// Lookup table for ball height to ADC value mapping (experimentally determined)
LUT height_lut[LOOKUP_TABLE_SIZE] = {
    {5, 3500},
    {10, 2667},
    {15, 2630},
    {20, 2233},
    {25, 1800},
		{30, 1315},
    {35, 1140},
    {40, 900},
    {45, 850},
    {50, 800}
};

// open/closed loop control flag (open=0)
volatile _Bool control_flag = 0;

// Initial height setpoint
int16_t setpoint = 1700;

// PID controller parameters
float Kp = 0.01;// Proportional gain
float Ki = 0.7; // Integral gain
float Kd = 0.7; // Derivative gain

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
uint16_t parse_height() {
	
	// parse height string
	char height_string[2];
	uint16_t height;
	int i;
	for (i = 0; i < 2; i++){
		height_string[i] = rx_buffer[i+4];
	}
	height = atoi(height_string); // convert string to HEX angle val
	
	// get value from the LUT
	int j;
	for (j = 0; j < LOOKUP_TABLE_SIZE; ++j) {
		if (height_lut[j].height == height) {
				return height_lut[j].adc;
		}
	}
	return 0; // return 0 if not present
}
void initial_boost(){
	write_dutycycle_PWM(0x04B0); // Start the ball at the bottom
	delay(8000000);
	write_dutycycle_PWM(0x0700); // Give it a little bit of lift
	delay(8000000);
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
