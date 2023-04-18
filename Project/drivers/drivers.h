/**
		Filename: drivers.h
		Description: This file defines/declares all drivers for for ENSE 481 Final Project
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-04-17
		Class: ense481
		Project: Ball Height Controller
*/

#ifndef DRIVERS_H
#define DRIVERS_H

#include <stm32f10x.h>
#include <stdint.h>

// Serial Communication global declarations
#define BUFFER_SIZE 64
extern uint8_t rx_buffer[BUFFER_SIZE];
extern uint8_t tx_buffer[BUFFER_SIZE];
extern uint8_t cursor;
extern volatile _Bool cmd_received_flag;

/** Configure the clock */
void open_clock(void);

/** Reset the clock registers */
void close_clock(void);

/** Enable the clocks */
void start_clock(void);

/** Stops the clock but keeps its configuration */
void stop_clock(void);

/** Configure GPIOA */
void open_portA(void);

/** Reset GPIOA */
void close_portA(void);

/** Configure GPIOA (PA5) for LED as 50 Mhz output*/
void open_LED(void);

/** Reset the state of GPIOA (PA5) */
void close_LED(void);

/** Turn on the LED */
void start_LED(void);

/** Turn off the LED */
void stop_LED(void);

/** Configure USART2 on APB2ENR */
void open_USART(void);

/** Undo everything done in open_USART */
void reset_USART(void);

/** Transmit a byte via USART2 */
void tx_USART(volatile uint8_t*);

/** See if data is ready to transmit 

		returns
			0: USART2 is not ready for transmission (TC=0)
			1: USART2 is readt for transmission (TC=1)
	*/
_Bool tx_ready_USART(void);

/** Read a byte from USART2 data register */
void rx_USART(uint8_t *pData);

/** See if data is ready to be read 

		returns
			0: USART2 rx data is not ready (RXNE=0)
			1: USART2 rx data is ready  (RXNE=1)
	*/
_Bool rx_ready_USART(void);

/** USART interrupt handler

		- stores characters in rx_buffer and send back the character
		- if character received is /r, set flag to handle CLI command
		- handles delete operator too
	*/
void USART2_IRQHandler(void);

/** Setup ADC1 on Port A P0 */
void open_ADC(void);

/** Start ADC1 on Port A P0 */
void start_ADC(void);

/** Stop ADC1 on Port A P0 */
void stop_ADC(void);

/** Disable ADC1 on Port A P0 */
void close_ADC(void);

/** Make an ADC reading

		returns
			adc_value: 16 bit adc reading
	*/
uint16_t read_ADC(void);

#endif
