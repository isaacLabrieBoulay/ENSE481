/**
		Filename: CLI.c
		Description: This file defines all CLI functions for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-17
		Class: ense481
		Project: lab1
*/
#include <stm32f10x.h>
#include "CLI.h"
#include "pwm.h"
#include "app.h"
#include "drivers.h"
#include "timer.h"
#include "time_trig_ops.h"
#include "time_opps.h"
#include <string.h>
#include <stdlib.h>


void init_message_CLI(){
	uint8_t message[] = "'morning. type 'help' for instructions.\r\n";
	send_message(message, sizeof(message));
}
uint8_t parser_CLI(uint8_t *comm){
	/* help command */
	if((comm[0] == 'h') && (comm[1] == 'e') && 
			(comm[2] == 'l') && (comm[3] == 'p')) {
		return 0;
	}
	/* LED ON command */
	else if ((comm[0] == 'o') && (comm[1] == 'n')){
		return 1;
	}
	/* LED OFF command */
	else if ((comm[0] == 'o') && (comm[1] == 'f') && (comm[2] == 'f')){
		return 2;
	}
	/* Query LED state command */
	else if ((comm[0] == 'q') && (comm[1] == 'u') && 
			(comm[2] == 'e') && (comm[3] == 'r') && (comm[4] == 'y')){
		return 3;
	}
	/* Date & Time Command */
	else if ((comm[0] == 'd') && (comm[1] == 'a') && 
			(comm[2] == 't') && (comm[3] == 'e')){
		return 4;
	}
	else if ((comm[0] == 't') && (comm[1] == 'i') && 
			(comm[2] == 'm') && (comm[3] == 'e') && (comm[4] == 'r')){
		return 5;
	}
	else if ((comm[0] == 'a') && (comm[1] == 'n') && 
			(comm[2] == 'g') && (comm[3] == 'l') && (comm[4] == 'e')){
				
				// parse the angle value from CLI
				char angle_string[3];
				uint16_t angle;
				int i;
				for (i = 0; i < 3; i++){
					angle_string[i] = comm[i+6];
				}
				angle = atoi(angle_string); // convert string to HEX angle val
				if (angle > 180)
					angle = 180;
				else if (angle < 0)
					angle = 0;
				
				write_dutycycle_PWM(angle);
				
		return 6;
	}
	/* If command is not recognized, show 'help' */
	else
		return 0;
}
void help_CLI(){
	uint8_t message1[] = "Available Commands are:\r\n";
	send_message(message1, sizeof(message1));
	uint8_t message2[] = "'help' - get list of available commands\r\n";
	send_message(message2, sizeof(message2));
	uint8_t message3[] = "'on' - turn on LD2\r\n";
	send_message(message3, sizeof(message3));
	uint8_t message4[]= "'off' - turn off LD2\r\n";
	send_message(message4, sizeof(message4));
	uint8_t message5[] = "'query' - query the state of LD2\r\n";
	send_message(message5, sizeof(message5));
	uint8_t message6[]= "'date' - get the time and date of last compilation\r\n";
	send_message(message6, sizeof(message6));
	uint8_t message7[]= "'timer' - get the execution time of operations\r\n";
	send_message(message7, sizeof(message7));
	uint8_t message8[]= "'angle(<degrees>)' - set the servo angle (000-180)\r\n";
	send_message(message8, sizeof(message8));
}
uint8_t carriage_return_CLI(uint8_t* rx_buffer_CLI, uint8_t* tx_buffer_CLI, uint8_t buffer_size, uint8_t cursor){
	tx_buffer_CLI[0] = '\n';
	tx_USART(tx_buffer_CLI); // display a carriage return on PuTTy
	clear_buffers(rx_buffer_CLI, tx_buffer_CLI, buffer_size); // clear both buffers
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
void send_time(uint16_t time){
	char str_nums[10] = "          ";
	double double_time = (double)time;
	// Convert time to a floating number string
	sprintf(str_nums, "%f", double_time);
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
	
	/* breaks code when I transfer the 1024 bytes at a time */
	
	// copy a 1024-byte struct using the assignment operator
	//uint8_t str_words8[] = "copy_1024bytes: ";
	//send_message(str_words8, sizeof(str_words8));
	//time = copy_1024bytes_AVG();
	//send_time(time);
	
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

void print_voltage(uint16_t adc_val){
	char str_nums[10] = "          ";
	// Convert adc_val to a voltage number string
	float voltage = (adc_val*3.3)/4096;
	sprintf(str_nums, "%f", voltage);
	str_nums[8] = '\r';
	str_nums[9] = '\n';
	send_message(str_nums, sizeof(str_nums));	
}
