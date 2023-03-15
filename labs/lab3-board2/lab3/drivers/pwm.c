#include <stm32f10x.h>
#include "pwm.h"

void start_PWM (void) {

		RCC->APB2ENR |= 1u<<3;	// bit 3: IOPBEN=1, enable GPIOB clock
	
		// Configure PB7 as TIM4_CH2
		GPIOB->CRL &= ~(1u<<30);// bits 31:28, output mode, 10MHz, alt func open drain
    GPIOB->CRL = GPIOB->CRL | 
									(0xBu<<28);
	
    RCC->APB1ENR |= 1u<<2;	// 1: enable clock for TIM4

		TIM4->PSC = 71;     		// set prescaler to 71 to achieve a 1us timebase for the timer
		TIM4->ARR = 19999; 			// set auto-reload after 20000 clks

    TIM4->CR1 = 0;     			// reset command register 1
    TIM4->CR2 = 0;     			// reset command register 2

    TIM4->CCR2  = 600;     	// Set channel 2 duty cycle of 600us

    TIM4->CCMR1 = 0x6000;   // Set channel 2 to PWM mode

		TIM4->CCER  = 0x10;  		// CC2E=1, set capture/compare on TIM4_CH2
    TIM4->SMCR  = 0;       	// 0 set slave mode control register

    TIM4->CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
			 // generates an update interrupt or DMA
			 // request if enabled.

    TIM4->CR2 = 0;        // 0x0 set command register 2

    TIM4->CR1 |= 1u<<0;   // 0: enable timer
}
/** Sample code from the lab 3 working project **/
void write_dutycycle_PWM (uint16_t angle) {
		
		// calculate duty cycle
		uint16_t dutyCycle = ((angle - MIN_ANGLE) * DUTY_CYCLE_RANGE / ANGLE_RANGE) + MIN_DUTY_CYCLE;
		TIM4->CCR2  = dutyCycle;     // Set duty cycle

} 