/**
		Filename: drivers.c
		Description: This file defines all driver functions for lab1
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-01-29
		Class: ense481
		Project: lab1
*/
#include "CLI.h"
#include "app.h"
#include "drivers.h"
#include <stm32f10x.h>
#include "app.h"

void open_clock(){
	// configure clocks
	RCC->CFGR = RCC->CFGR |
							(1u<<1)	  | // bit 1:0, SW = 10, select PLL as system clock
							(1u<<16)  | // bit 16, PLLSRC=1, sets PLL clock source to HSE osc.
							(2u<<18);   // bit 21:18, PLLMUL=0010, PLL input clock x4
}
void close_clock(){
	// Reset the clock according to RM reset value
	RCC->CFGR = 0x00000000;
}
void start_clock() {
	// enable clocks
	RCC->CR = RCC->CR  |
						(1u) 		 |	 // bit 0, HSION=1, enable internal 8 MHz RC oscillator
						(1u<<16) |	 // bit 16, HSEON=1, enable HSE oscillator
						(1u<<24); 	 // bit 24, PLLON=1, enable pll

	uint32_t temp = 0x00;
	while (temp != 0x02000000){ 		// Wait for the PLL to stabilize
		temp = RCC->CR & 0x02000000; 	//Check to see if the PLL lock bit is set
	}
}
void stop_clock(){
	RCC->CR = 0x00000083;
}
void open_portA(){
	RCC->APB2ENR |= (1u<<2);	  // bit 2, IOPAEN=1, IO port A clock enable
}
void close_portA(){
	RCC->APB2ENR &= ~(1u<<2);	  // bit 2, IOPAEN=0, IO port A clock disable
}
void open_LED(){
	GPIOA->CRL = GPIOA->CRL |
							 (1u<<20)   | 
							 (1u<<21); 	    // bit 21:20, MODEA=11, output mode, 50 MHz
	GPIOA->CRL &= ~((1u<<22) |
									(1u<<23));	// bit 23:22, CFNA=00, General purpose output push-pull						 
}
void close_LED(){
	GPIOA->CRL &= ~((1u<<20) | 
								 (1u<<21));   // bit 21:20, MODEA=00, (reset state)
	GPIOA->CRL |= (1u<<22);
	GPIOA->CRL &= ~(1u<<23);	  // bit 23:22, CFNA=01, Floating input (reset state)
}
void start_LED(){
	GPIOA->ODR |=  (1u<<5);     // bit 5, GPIOA=ON
}
void stop_LED(){
	GPIOA->ODR &= ~(1u<<5);     // bit 5, GPIOA=OFF
}
void open_USART(){
	
	// Enable USART2 clock	
	RCC->APB1ENR |= (1u<<17);   // bit 17, USART2EN=1, USART2 clock enabled	
	
	// Enable the USART2 pins on port A
	// USART2_Tx=PA.02 (alt. func. output)
	GPIOA->CRL = GPIOA->CRL |
							 (1u<<9)    | 
							 (1u<<8); 			// bit 9:8, MODEA=11, output mode, 50 MHz
	GPIOA->CRL |= (1u<<11);
	GPIOA->CRL &= ~(1u<<10);	  // bit 11:10, CFNA=10, Alternate function output Push-pull
  // USART2_Rx=PA.03
	//GPIOA->CRL |= (1u<<12); 
	//GPIOA->CRL &= ~(1u<<13); 		// bit 13:12, MODEA=01, floating input
	//GPIOA->CRL &= ~((1u<<14) |
	//								(1u<<15));	// bit 15:14, CFNA=00, Input mode
	
	GPIOA->CRL &= ~((1u<<12) |
									(1u<<13));    // bit 13:12, MODEA=00, input mode
	GPIOA->CRL |= (1u<<14);
	GPIOA->CRL &= ~(1u<<15);			// bit 15:14, CFNA=01, floating input
	
	
	// Enable USART2
	USART2->CR1 |= (1u<<13);    // bit 13, UE=1, USART enabled 
	
		/** baud rate config. **/
	// baud rate = fclk/(16*USART_DIV)
	//  where, fclk = PCLK1 for USART2 (set to 36 MHz by SystemClockInitTo72())
	//  
	// USART_DIV = 36MHz/(16*115200) = 19.53
	//
	// Mantissa = 0d19 (or 0x13)
	// fraction = d0.53 so 16*0.53 = ~8 (or 0x8)
	// Finally, USART_BRR = 0x130 + 0x8 = 0x138
	USART2->BRR |= (0x138);     // 115200 Baud, note that this register is 0x0000 by default
	
	// Set word size to 8
	USART2->CR1 &= ~(1u<<12);    // bit 12, M=0, 8 data bits
	
	//Set stop bit
	USART2->CR2 &= ~((1u<<12) |
									(1u<<13));   // bit13:12, STOP=00, 1 stop bit
	
	USART2->CR1 = USART2->CR1 |
								(1u<<2)   	|	 // bit 2, RE=1, USART receiver enabled
								(1u<<3);		 	 // bit 3, TE=1, USART transmitter enable
}
void reset_USART(){
	
	/* Disable USART2 clock	*/
	RCC->APB1ENR &= ~(1u<<17);   // bit 17, USART2EN=1, USART2 clock disabled	
	/* Reset GPIOA P2 and P3
		 USART2_Tx=PA.02 (alt. func. output) */
	GPIOA->CRL &= ~((1u<<8)  | 
							  (1u<<9)); 		// bit 9:8, MODEA=00, reset state
	GPIOA->CRL |= (1u<<10);
	GPIOA->CRL &= ~(1u<<11);		// bit 11:10, CFNA=01, reset state
  /* USART2_Rx=PA.03 */
	GPIOA->CRL &= ~((1u<<12) |
								(1u<<13));		// bit 13:12, MODEA=00, reset state
	GPIOA->CRL |= (1u<<14);
	GPIOA->CRL &= ~(1u<<15);	// bit 15:14, CFNA=01, reset state
	/* Enable USART2 */
	USART2->CR1 &= ~(1u<<13);    // bit 13, UE=0, USART disabled 
	/* Set baud rate to reset value */
	USART2->BRR &= ~(0xFFFF0000) ;     // 0xXXXX0000
	/* word size */
	USART2->CR1 &= ~(1u<<12);    // bit 12, M=0, 8 data bits
	/* Already default */
	USART2->CR2 &= ~((1u<<12) |
									(1u<<13));   // bit13:12, STOP=00, 1 stop bit
	USART2->CR1 &= ~((1u<<2)  |	 // bit 2, RE=0, USART receiver disabled
									(1u<<3));		 	 // bit 3, TE=0, USART transmitter disabled
}
void tx_USART(volatile uint8_t* pdata){
	USART2->DR = *pdata;
	while(!(tx_ready_USART())); // Wait until transmission is complete
}
_Bool tx_ready_USART(){
	return USART2->SR & (1u<<6);
}
void rx_USART(uint8_t* pdata){
	/* Return the character */
	*pdata = (uint8_t)USART2->DR & 0xFF;
}
_Bool rx_ready_USART(void){
	uint8_t val = (USART2->SR & 1u<<5);
	return val;
}
void open_ADC(void){
	
	// GPIO config, Port C
	RCC->APB2ENR |= (1u<<4); //bit4, IOPC=1, Port C enabled
	// Configure pin 0 on port C as analog input
	GPIOC->CRL &= ~((1u) 		| 
									(1u<<1) |  // bit1:0, MODE0=00, input mode
									(1u<<2) |
									(1u<<3));  // bit3:2, CNF0=00, analog mode
	
	// Enable clock for ADC1 config
  RCC->APB2ENR |= (1u<<9);	 // bit9. ADC1=1, Enable the ADC1 clock
	

	
	// Set up ADC1, channel 10
	ADC1->SMPR1 = ADC1->SMPR1 |
								(1u) 				|	
								(1u<<2); 		 // Channel 10 has sample time of 55.5 cycles
														 // one conversion therefore SQR2 is left with reset value
	ADC1->SQR3 = ADC1->SQR3 |
							 (1u<<1) 		|
							 (1u<<3);		// First and only conversion in sequence in chan10
}
void start_ADC(void){

	// Enable the ADC1
	ADC1->CR2 |= (1u); //bit0, ADON=1, Enable ADC
	
	// Calibrate ADC1
	ADC1->CR2 |= (1u<<2);
	while ((ADC1->CR2 & (1u<<2)) != 0); // bit = 0 once a calbiration is done
}
void stop_ADC(void){
	ADC1->CR2 &= ~(1u<<0); //bit0, ADON=0, Stop ADC1
}
void close_ADC(void){

	// Put Port C, pin 0 in reset state
	GPIOC->CRL |= 0x00000004;  //bit3:0, CNF0=01, floating input, MODE0=00, Input mode

	// Reset all registers I modified for ADC1
	ADC1->SMPR1 = 0x00000000;
	ADC1->SQR3 = 0x00000000;
	
	// Disable clock for ADC1 config
  RCC->APB2ENR &= ~(1u<<9);// bit9. ADC1=0, Disable ADC1 clock
}
uint16_t read_ADC(void){
	
	uint16_t adc_value;
	
	ADC1->CR2 |= (1u); //bit0, ADON=1, Start conversion by writing a 1 to an already 1 ADON.

	// Wait for conversion to complete (EOC=1)
	while ((ADC1->SR & (1u<<1)) == 0){};

	// Read ADC value from data register
	adc_value = ADC1->DR;
	
	return adc_value;
}