/**
		Filename: time_opps.c
		Description: This file defines all basic operations to time
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-17
		Class: ense481
		Project: lab2
*/
#include <stdint.h>
#include "time_opps.h"
#include "timer.h"
#include "app.h"

#define MAX (18446744073709551615ULL) // biggest 64 bit number

struct s8{
	double a;
};

struct s128{
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
	double g;
	double h;
	double i;
	double j;
	double k;
	double l;
	double m;
	double n;
	double o;
	double p;
};

struct s1024{
	double a[8];
	double b[8];
	double c[8];
	double d[8];
	double e[8];
	double f[8];
	double g[8];
	double h[8];
	double i[8];
	double j[8];
	double k[8];
	double l[8];
	double m[8];
	double n[8];
	double o[8];
	double p[8];
};

uint64_t get_random_64bit_number(void){
	
	// Uses counter to seed pseudorandom number
	// since it is only 16 bit, has to be read 4 times (4*16)
	volatile uint16_t seed_0_15 = timer_start(); //bit 16:0
	delay(100); // use counter time to generate random delay before next read
	volatile uint16_t seed_16_31 = timer_start(); //bit 31:15
	delay(1000);
	volatile uint16_t seed_32_47 = timer_start(); //bit 47:32
	delay(700);
	volatile uint16_t seed_48_63 = timer_start(); //bit 16:0
	
	// combine into one big word
	volatile uint64_t seed = ((uint64_t) seed_48_63 << 48) +
									((uint64_t) seed_32_47 << 32) +
									((uint64_t) seed_16_31 << 16) + 
									 seed_0_15;

	// 64-bit Linear Congruential Generator (https://nuclear.llnl.gov/CNP/rng/rngman/node4.html)
	volatile uint64_t rand = (seed * 6364136223846793005ULL + 1442695040888963407ULL) % MAX;
	return rand;
}
uint16_t add_random_32(){
	
	// get random numbers
	volatile uint64_t rand64 = get_random_64bit_number();
	volatile uint32_t rand1 = (uint32_t)(rand64 &0xFFFFFFFF);
	volatile uint32_t rand2 = (uint32_t)((rand64 &0xFFFFFFFF00000000)>>32);
	
	volatile uint16_t time_start = timer_start();
	volatile uint64_t addition = rand1 + rand2;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float add_random_32_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += add_random_32();
	}
	return ((float)sum)/100;
}
uint16_t add_random_64(){
	
	// get random numbers
	volatile uint64_t rand1 = get_random_64bit_number();
	volatile uint64_t rand2 = get_random_64bit_number();
	
	volatile uint16_t time_start = timer_start();
	volatile uint64_t addition = rand1 + rand2;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float add_random_64_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += add_random_64();
	}
	return ((float)sum)/100;
}
uint16_t mult_random_32(){
	
	// get random numbers
	volatile uint64_t rand64 = get_random_64bit_number();
	volatile uint32_t rand1 = (uint32_t)(rand64 &0xFFFFFFFF);
	volatile uint32_t rand2 = (uint32_t)((rand64 &0xFFFFFFFF00000000)>>32);
	
	volatile uint16_t time_start = timer_start();
	volatile uint64_t multiplication = ((uint64_t)rand1)*((uint64_t)rand2);
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float mult_random_32_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += mult_random_32();
	}
	return ((float)sum)/100;
}
uint16_t mult_random_64(){
	
	// get random numbers
	volatile uint64_t rand1 = get_random_64bit_number();
	volatile uint64_t rand2 = get_random_64bit_number();
	
	volatile uint16_t time_start = timer_start();
	volatile uint64_t multiplication = rand1*rand2;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float mult_random_64_AVG(void){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += mult_random_64();
	}
	return ((float)sum)/100;
}
uint16_t div_random_32(){
	
	// get random numbers
	volatile uint64_t rand64 = get_random_64bit_number();
	volatile uint32_t rand1 = (uint32_t)(rand64 &0xFFFFFFFF);
	volatile uint32_t rand2 = (uint32_t)((rand64 &0xFFFFFFFF00000000)>>32);
	
	volatile uint16_t time_start = timer_start();
	volatile float division = ((float)rand1)/((float)rand2);
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float div_random_32_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += div_random_32();
	}
	return ((float)sum)/100;
}
uint16_t div_random_64(){
	
	// get random numbers
	volatile uint64_t rand1 = get_random_64bit_number();
	volatile uint64_t rand2 = get_random_64bit_number();
	
	volatile uint16_t time_start = timer_start();
	volatile double division = ((double)rand1)/((double)rand2);
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float div_random_64_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += div_random_64();
	}
	return ((float)sum)/100;
}
uint16_t copy_8bytes(){
	struct s8 s1 = {0xFFFFFFFF};
	struct s8 s2;
	
	volatile uint16_t time_start = timer_start();
	s2 = s1;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float copy_8bytes_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += copy_8bytes();
	}
	return ((float)sum)/100;
}
uint16_t copy_128bytes(){
	
	struct s128 s1 = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
										0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
										0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
										0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};
	
	struct s128 s2;
	
	volatile uint16_t time_start = timer_start();
	s2 = s1;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float copy_128bytes_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += copy_128bytes();
	}
	return ((float)sum)/100;
}
uint16_t copy_1024bytes(){
	/**
	struct s1024 s1 = {{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
										 {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF}};
	*/
	struct s1024 s1;
	struct s1024 s2;
	
	volatile uint16_t time_start = timer_start();
	s2 = s1;
	volatile uint16_t elapsed_time = timer_stop(time_start);
	
	return elapsed_time;
}
float copy_1024bytes_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 100; i++){
		sum += copy_1024bytes();
	}
	return ((float)sum)/100;
}