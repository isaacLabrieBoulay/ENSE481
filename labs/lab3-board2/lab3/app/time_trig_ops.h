/**
		Filename: time_trig_opps.h
		Description: This file declares all trig timing functions
		Author: Isaac Labrie-Boulay (200391860)
		Date: 2023-02-17
		Class: ense481
		Project: lab2
*/

#ifndef TIME_TRIG_OPPS_H
#define TIME_TRIG_OPPS_H
#include <stdint.h>
#include <math.h>

/** time cos(x) operation from math.h library

		returns 
			time
	*/
uint16_t standard_cos(float);

/** return average runtime for cos(x) operation from math.h library

		returns 
			average time (n=100)
	*/
float standard_cos_AVG(void);

/** time sin(x) operation from math.h library

		returns 
			time
	*/
uint16_t standard_sin(float);

/** return average runtime for sin(x) operation from math.h library

		returns 
			average time (n=100)
	*/
float standard_sin_AVG(void);

/** time 12-segment sin algorithm operation from Jack W. Crenshaw, Math Toolkit for
			Real-Time Development

		returns 
			time
	*/
uint16_t seg_sin(float);

/** return average runtime for 12-segment sin

		returns 
			average time (n=100)
	*/
float segsin_AVG(void);

/** time 12-segment cos algorithm operation from Jack W. Crenshaw, Math Toolkit for
			Real-Time Development

		returns 
			time
	*/
uint16_t seg_cos(float);

/** return average runtime for 12-segment cos

		returns 
			average time (n=100)
	*/
float segcos_AVG(void);
#endif
