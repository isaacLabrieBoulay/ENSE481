/**
		Filename: CLI.c
		Description: This file defines all CLI functions for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#include "CLI.h"

void init_message_CLI(){
	uint8_t message[] = "'morning. type 'help' for instructions.\r\n";
	send_message(message, sizeof(message));
}
void handle_CLI(){
	
	uint8_t action = parser_CLI();
	uint16_t angle = 0;
	uint16_t height = 0;
	
	switch(action){
		case 0: // help
			help_CLI();
			break;
		case 1: // date & time
			date_and_time_CLI();
			break;
		case 2: // timer script
			timer_CLI(); // print out times
			break;
		case 3: // change angle
			angle = parse_angle();
			write_angle_PWM(angle);
			break;
		case 4: // disable control
			control_flag = 0;
			break;
		case 5: // enable control
			control_flag = 1;
			break;
		case 6: // set height of ball
			height = parse_height();
		  setpoint = height;
			break;
		default:
			help_CLI(); // defaults to the help command
			break;
	}
	cursor = carriage_return_CLI();
}
uint8_t parser_CLI(){
	/* help command */
	if((rx_buffer[0] == 'h') && (rx_buffer[1] == 'e') && 
		 (rx_buffer[2] == 'l') && (rx_buffer[3] == 'p'))
		return 0;
	/* Date & Time Command */
	else if ((rx_buffer[0] == 'd') && (rx_buffer[1] == 'a') && 
					 (rx_buffer[2] == 't') && (rx_buffer[3] == 'e'))
		return 1;
	else if ((rx_buffer[0] == 't') && (rx_buffer[1] == 'i') && 
					 (rx_buffer[2] == 'm') && (rx_buffer[3] == 'e') && (rx_buffer[4] == 'r'))
		return 2;
	else if ((rx_buffer[0] == 'a') && (rx_buffer[1] == 'n') && 
					 (rx_buffer[2] == 'g') && (rx_buffer[3] == 'l') && (rx_buffer[4] == 'e'))
		return 3;
	else if ((rx_buffer[0] == 'o') && (rx_buffer[1] == 'p') && 
					 (rx_buffer[2] == 'e') && (rx_buffer[3] == 'n'))
		return 4;
	else if ((rx_buffer[0] == 'c') && (rx_buffer[1] == 'l') && 
					 (rx_buffer[2] == 'o') && (rx_buffer[3] == 's') && (rx_buffer[4] == 'e'))
		return 5;
	else if ((rx_buffer[0] == 's') && (rx_buffer[1] == 'e') && 
				   (rx_buffer[2] == 't'))
		return 6;
	/* If command is not recognized, show 'help' */
	else
		return 0;
}
void send_message(uint8_t *pdata, uint8_t size){
	uint8_t buffer_index = 0;
	while(buffer_index < size){
		buffer_index++;// increment counter
		tx_USART(pdata);//transmit data at pdata
		pdata++;// increment pointer
	}
}
void help_CLI(){
	uint8_t message1[] = "Available Commands are:\r\n";
	send_message(message1, sizeof(message1));
	uint8_t message2[] = "'help' - get list of available commands\r\n";
	send_message(message2, sizeof(message2));
	uint8_t message3[]= "'date' - get the time and date of last compilation\r\n";
	send_message(message3, sizeof(message3));
	uint8_t message4[]= "'timer' - get the execution time of operations\r\n";
	send_message(message4, sizeof(message4));
	uint8_t message5[]= "'angle(<degrees>)' - set the servo angle (000-180)\r\n";
	send_message(message5, sizeof(message5));
	uint8_t message6[]= "'open' - disable closed loop control (default state)\r\n";
	send_message(message6, sizeof(message6));
	uint8_t message7[]= "'close' - enable closed loop PID control \r\n";
	send_message(message7, sizeof(message7));
	uint8_t message8[]= "'set(<cm>)' - change the ball height to a specified height in cm. \r\n";
	send_message(message8, sizeof(message8));
}
void clear_buffers(){
	/* zero all indeces of Tx/Rx buffers */
	int i;
	for (i = 0; i < 50; i++){
		rx_buffer[i] = 0x00;
		tx_buffer[i] = 0x00;
	}
}
uint8_t carriage_return_CLI(){
	tx_buffer[0] = '\n';
	tx_USART(tx_buffer); // display a carriage return on PuTTy
	clear_buffers(); // clear both buffers
	cursor = 0; // Reset the cursor to 0 after return
	return cursor;
}
void date_and_time_CLI(){
	uint8_t date[] = __DATE__; // date macro converted to string
	send_message(date, sizeof(date));
	uint8_t comma[] = ", ";
	send_message(comma, sizeof(comma));
	uint8_t time[] = __TIME__;
	send_message(time, sizeof(time)); // time macro converted to string
	uint8_t ret[] = "\r\n";
	send_message(ret, sizeof(ret));
	
}
void send_uint(uint16_t number){
	uint8_t str_nums[10] = "          ";
	// Convert time to a floating number string
	sprintf((char*)str_nums, "%d", number);
	str_nums[8] = '\r';
	str_nums[9] = '\n';
	send_message(str_nums, sizeof(str_nums));	
}
void send_float(float value){
	uint8_t buffer[32];
	sprintf((char*)buffer, "%.2f", value);
	buffer[30] = '\r';
	buffer[31] = '\n';
	send_message(buffer, sizeof(buffer));	
	
}
void send_time(uint16_t time){
	uint8_t str_nums[10] = "          ";
	double double_time = (double)time;
	// Convert time to a floating number string
	sprintf((char*)str_nums, "%f", double_time);
	str_nums[8] = '\r';
	str_nums[9] = '\n';
	send_message(str_nums, sizeof(str_nums));	
}
void timer_CLI(){
	
	float time;
	
	uint8_t preface[] = "Average tick counts: \r\n";
	send_message(preface, sizeof(preface));
	
	// add two random 32-bit integers
	uint8_t str_words[] = "add32: ";
	send_message(str_words, sizeof(str_words));
	time = add_random_32_AVG();
	send_time(time);

	// add two random 64-bit integers
	uint8_t str_words1[] = "add64: ";
	send_message(str_words1, sizeof(str_words1));
	time = add_random_64_AVG();
	send_time(time);

	// multiply two random 32-bit integers
	uint8_t str_words2[] = "mult32: ";
	send_message(str_words2, sizeof(str_words2));
	time = mult_random_32_AVG();
	send_time(time);

	// multiply two random 64-bit integers
	uint8_t str_words3[] = "mult64: ";
	send_message(str_words3, sizeof(str_words3));
	time = mult_random_64_AVG();
	send_time(time);
	
	// divide two random 32-bit integers
	uint8_t str_words4[] = "div32: ";
	send_message(str_words4, sizeof(str_words4));
	time = div_random_32_AVG();
	send_time(time);
	
	// divide two random 64-bit integers
	uint8_t str_words5[] = "div64: ";
	send_message(str_words5, sizeof(str_words5));
	time = div_random_64_AVG();
	send_time(time);
	
	// copy an 8-byte struct using the assignment operator
	uint8_t str_words6[] = "copy8bytes: ";
	send_message(str_words6, sizeof(str_words6));
	time = copy_8bytes_AVG();
	send_time(time);
	
	// copy a 128-byte struct using the assignment operator
	uint8_t str_words7[] = "copy128bytes: ";
	send_message(str_words7, sizeof(str_words7));
	time = copy_128bytes_AVG();
	send_time(time);
	
	// calculate sin (math.h)
	uint8_t str_words9[] = "standardsin: ";
	send_message(str_words9, sizeof(str_words9));
	time = standard_sin_AVG();
	send_time(time);
	
	// calculate cos (math.h)
	uint8_t str_words10[] = "standardcos: ";
	send_message(str_words10, sizeof(str_words10));
	time = standard_cos_AVG();
	send_time(time);
	
	// calculate sin (12 segment)
	uint8_t str_words11[] = "12segsin: ";
	send_message(str_words11, sizeof(str_words11));
	time = segsin_AVG();
	send_time(time);
	
	// calculate cost (12 segment)
	uint8_t str_words12[] = "12segcos: ";
	send_message(str_words12, sizeof(str_words12));
	time = segcos_AVG();
	send_time(time);
}
uint16_t parse_angle(){// parse the angle value from CLI
	char angle_string[3];
	uint16_t angle;
	int i;
	for (i = 0; i < 3; i++){
		angle_string[i] = rx_buffer[i+6];
	}
	angle = atoi(angle_string); // convert string to HEX angle val
	if (angle > 180)
		angle = 180;
	
	return angle;
}
void print_voltage(uint16_t adc_val){
	uint8_t str_nums[10] = "          ";
	// Convert adc_val to a voltage number string
	float voltage = (adc_val*3.3)/4096;
	sprintf((char*)str_nums, "%f", voltage);
	str_nums[8] = '\r';
	str_nums[9] = '\n';
	send_message(str_nums, sizeof(str_nums));	
}
