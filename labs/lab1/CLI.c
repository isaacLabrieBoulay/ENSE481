/**
		Filename: CLI.c
		Description: This file defines all CLI functions for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-01-29
		Class: ense481
		Project: lab1
*/

#include <stm32f10x.h>
#include "CLI.h"
#include "app.h"
#include "drivers.h"

void init_message_CLI(void){
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