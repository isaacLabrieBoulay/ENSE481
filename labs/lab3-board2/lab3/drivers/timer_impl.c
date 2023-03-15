/**
		Filename: timer_impl.c
		Description: This file defines all timer drivers for lab2
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-15
		Class: ense481
		Project: lab2
*/
#include <stm32f10x.h>
#include "timer.h"

void timer_init(void){
	RCC->APB1ENR |= (1u);
	
	TIM2->CR1 &= ~((1u<<9) | // bit9:8. CKD=00, no clock division
							   (1u<<8)); 
	TIM2->CR1 = TIM2->CR1 |
							(1u<<4)		| // bit4, DIR=1, count down
							(1u);				// bit0, CEN=1, counter enabled 
							
	
}
int16_t timer_start(void){
	uint16_t time;
	time = (uint16_t)TIM2->CNT & 0xFFFF;
	return time;
}
int16_t timer_stop(uint16_t start_time){
	
	uint16_t current_time;
	current_time = (uint16_t)TIM2->CNT & 0xFFFF;
	uint16_t elapsed_time;
	if(current_time > start_time){ // compute rollover time
		elapsed_time = (0xFFFF - current_time) + start_time;
	}
	else{ // no rollover, simply compute the difference
		elapsed_time = start_time - current_time;
	}
	return elapsed_time;
}
void timer_shutdown(void){
	RCC->APB1ENR &= ~(1u);
	
	TIM2->CR1 &= ~((1u<<4) | // bit4, DIR=1, count down
							   (1u));		 // bit0, CEN=1, counter enabled 
}
