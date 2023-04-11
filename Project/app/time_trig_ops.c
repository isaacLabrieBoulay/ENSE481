/**
		Filename: time_trig_ops.c
		Description: This file defines all all trig timing functions
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-17
		Class: ense481
		Project: lab2
*/
#include <stdint.h>
#include <math.h>
#ifndef  M_PI
#define  M_PI  3.14159265358 // define for pi
#endif
#include "time_opps.h"
#include "time_trig_ops.h"
#include "timer.h"
#include "app.h"

#define cos_30 sqrt(3)/2
#define sin_30 1/2
#define pi_over_six M_PI/6 // pi/6
uint16_t standard_cos(float angle){
	volatile uint16_t time_start = TIM2_start();
	volatile float cosine = cos(angle);
	volatile uint16_t elapsed_time = TIM2_stop(time_start);
	
	return elapsed_time;
}
float standard_cos_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 360; i++){
		// convert degree to rad first
		float rad = (float)i*(M_PI/180.0);
		sum += standard_cos(rad);
	}
	return ((float)sum)/360;
}
uint16_t standard_sin(float angle){
	
	volatile uint16_t time_start = TIM2_start();
	volatile float sine = sin(angle);
	volatile uint16_t elapsed_time = TIM2_stop(time_start);
	
	return elapsed_time;
}
float standard_sin_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 360; i++){
		// convert degree to rad first
		float rad = (float)i*(M_PI/180.0);
		sum += standard_sin(rad);
	}
	return ((float)sum)/360;
}
// Taken from Jack W. Crenshaw, Math Toolkit for Real-Time Development
uint16_t seg_sin(float x){
	
	volatile uint16_t time_start = TIM2_start();
	
	float s;
	long n = (float)(x/pi_over_six + 0.5);
	x -= (float)n * pi_over_six;
	n = n % 12;
	if(n < 0)
		n += 12;
	float z = x*x;
	float s1 = ((z/20.0-1.0)*z/6.0+1.0)*x;
	float c1 = ((z/30.0+1.0)*z/12.0-1.0)*z/2.0+1.0;
	
	switch(n){
	case 0:
		s = s1;
		break;
	case 1:
		s = cos_30 * s1 + sin_30 * c1;
		break;
	case 2:
		s = sin_30 * s1 + cos_30 * c1;
		break;
	case 3:
		s = c1;
	break;
	case 4:
		s = -sin_30 * s1 + cos_30 * c1;
		break;
	case 5:
		s = -cos_30 * s1 + sin_30 * c1;
		break;
	case 6:
		s = -s1;
		break;
	case 7:
		s = -cos_30 * s1 - sin_30 * c1;
		break;
	case 8:
		s = -sin_30 * s1 - cos_30 * c1;
		break;
	case 9:
		s = -c1;
		break;
	case 10:
		s = sin_30 * s1 - cos_30 * c1;
		break;
	case 11:
		s = cos_30 * s1 - sin_30 * c1;
		break;
	}
	
	volatile uint16_t elapsed_time = TIM2_stop(time_start);
	
	return elapsed_time;
}
float segsin_AVG(){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 360; i++){
		sum += seg_sin(i);
	}
	return ((float)sum)/360;
}
// Taken from Jack W. Crenshaw, Math Toolkit for Real-Time Development
uint16_t seg_cos(float x){
	
	volatile uint16_t time_start = TIM2_start();
	
	float c;
	long n = (long)(x/pi_over_six + 0.5);
	x -= (float)n * pi_over_six;
	n = n % 12;
	if(n < 0)
		n += 12;
	float z = x*x;
	float s1 = ((z/20.0-1.0)*z/6.0+1.0)*x;
	float c1 = ((z/30.0+1.0)*z/12.0-1.0)*z/2.0+1.0;
	
	switch(n){
	case 0:
		c = c1;
		break;
	case 1:
		c = -sin_30 * s1 + cos_30 * c1;
		break;
	case 2:
		c = -cos_30 * s1 + sin_30 * c1;
		break;
	case 3:
		c = -s1;
		break;
	case 4:
		c = -cos_30 * s1 - sin_30 * c1;
		break;
	case 5:
		c = -sin_30 * s1 - cos_30 * c1;
		break;
	case 6:
		c = -c1;
		break;
	case 7:
		c = sin_30 * s1 - cos_30 * c1;
		break;
	case 8:
		c = cos_30 * s1 - sin_30 * c1;
		break;
	case 9:
		c = s1;
		break;
	case 10:
		c = cos_30 * s1 + sin_30 * c1;
		break;
	case 11:
		c = sin_30 * s1 + cos_30 * c1;
		break;
	}
	volatile uint16_t elapsed_time = TIM2_stop(time_start);
	
	return elapsed_time;
}
float segcos_AVG(void){
	
	float sum = 0;
	
	int i;
	for(i = 0; i < 360; i++){
		sum += seg_cos(i);
	}
	return ((float)sum)/360;
}
