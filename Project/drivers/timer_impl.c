/**
		Filename: timer_impl.c
		Description: This file defines all timer drivers for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/
#include "timer.h"

void TIM2_init(void){
	RCC->APB1ENR |= (1u);
	TIM2->CR1 &= ~((1u<<9) | // bit9:8. CKD=00, no clock division
							   (1u<<8)); 
	TIM2->CR1 = TIM2->CR1 |
							(1u<<4)		|  // bit4, DIR=1, count down
							(1u);				 // bit0, CEN=1, counter enabled 	
}
void TIM3_init(void){
	RCC->APB1ENR |= (1u<<1);
	TIM3->PSC = 7199;        // set prescaler to 71999 to achieve a 0.1ms timebase for the counter
	TIM3->ARR = 10000; 			 // set auto-reload after 10000 ticks
	TIM3->CR1 |= TIM_CR1_CEN;
}
int16_t TIM2_start(void){
	uint16_t time;
	time = (uint16_t)TIM2->CNT & 0xFFFF;
	return time;
}
uint16_t TIM3_read(void){
	return TIM3->CNT;
}
int16_t TIM2_stop(uint16_t start_time){
	
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

void TIM2_shutdown(void){
	RCC->APB1ENR &= ~(1u);
	
	TIM2->CR1 &= ~((1u<<4) | // bit4, DIR=1, count down
							   (1u));		 // bit0, CEN=1, counter enabled 
}
void TIM3_shutdown(void){
	RCC->APB1ENR &= ~(1u);
	
	TIM2->CR1 &= ~((1u<<4) | // bit4, DIR=1, count down
							   (1u));		 // bit0, CEN=1, counter enabled 
}
