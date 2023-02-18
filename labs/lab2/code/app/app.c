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
#include "app.h"
#include <stm32f10x.h>
#include <stdio.h>
#include <stdlib.h>

void delay(uint32_t wait_time){
	uint32_t tick = 0;
	while(1){
		if (tick == wait_time)
			break;
		else
			tick++;
	}
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
void send_message(uint8_t *pdata, uint8_t size){
	uint8_t buffer_index = 0;
	while(buffer_index < size){
		buffer_index++;// increment counter
		tx_USART(pdata);//transmit data at pdata
		pdata++;// increment pointer
	}
}
