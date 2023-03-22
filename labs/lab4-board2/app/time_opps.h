/**
		Filename: time_opps.h
		Description: This file declares all basic operation functions to time
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-17
		Class: ense481
		Project: lab2
*/
#ifndef TIME_OPPS_H
#define TIME_OPPS_H
#include <stdint.h>

/** Generate Random Number

		returns 
			64 bit randon number
	*/
uint64_t get_random_64bit_number(void);

/** time addition of 32 bit integers

		returns 
			time
	*/
uint16_t add_random_32(void);

/** return average runtime for 32 bit addition

		returns 
			average time (n=100)
	*/
float add_random_32_AVG(void);

/** time addition of 64 bit integers

		returns 
			time
	*/
uint16_t add_random_64(void);

/** return average runtime for 64 bit addition

		returns 
			average time (n=100)
	*/
float add_random_64_AVG(void);

/** time multiplication of 32 bit integers

		returns 
			time
	*/
uint16_t mult_random_32(void);

/** return average runtime for 32 bit multiplication

		returns 
			average time (n=100)
	*/
float mult_random_32_AVG(void);

/** time multiplication of 64 bit integers

		returns 
			time
	*/
uint16_t mult_random_64(void);

/** return average runtime for 64 bit multiplication

		returns 
			average time (n=100)
	*/
float mult_random_64_AVG(void);

/** time division of 32 bit integers

		returns 
			time
	*/
uint16_t div_random_32(void);

/** return average runtime for 32 bit division

		returns 
			average time (n=100)
	*/
float div_random_32_AVG(void);

/** time division of 64 bit integers

		returns 
			time
	*/
uint16_t div_random_64(void);

/** return average runtime for 64 bit division

		returns 
			average time (n=100)
	*/
float div_random_64_AVG(void);

/** time copying 8 byte struct

		returns 
			time
	*/
uint16_t copy_8bytes(void);

/** return average runtime of copying 8 byte struct

		returns 
			average time (n=100)
	*/
float copy_8bytes_AVG(void);

/** time copying 128 byte struct

		returns 
			time
	*/
uint16_t copy_128bytes(void);

/** return average runtime of copying 128 byte struct

		returns 
			average time (n=100)
	*/
float copy_128bytes_AVG(void);

/** time copying 1024 byte struct **BROKEN**

		returns 
			time
	*/
uint16_t copy_1024bytes(void);

/** return average runtime of copying 1024 byte struct

		returns 
			average time (n=100)
	*/
float copy_1024bytes_AVG(void);
#endif
