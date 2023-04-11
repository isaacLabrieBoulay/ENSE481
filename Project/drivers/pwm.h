#ifndef PWM_H
#define PWM_H
#include <stm32f10x.h>
#include <stdint.h>

#define MIN_ANGLE 0 // minimum angle in degrees
#define MAX_ANGLE 90 // maximum angle in degrees
#define MIN_DUTY_CYCLE 600 // minimum duty cycle in us
#define MAX_DUTY_CYCLE 1500 // maximum duty cycle in us
#define ANGLE_RANGE (MAX_ANGLE - MIN_ANGLE) // angle range in degrees
#define DUTY_CYCLE_RANGE (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) // duty cycle range in us

void start_PWM (void);
void write_angle_PWM (uint16_t);
void write_dutycycle_PWM(uint16_t);

#endif