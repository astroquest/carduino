/*
definition of pinouts based on the MEGA microcontrollers
*/

#ifndef CONFIGMEGA_H
#define CONFIGMEGA_H

typedef const int DigPin;
typedef const int PwmPin;

PwmPin pwm_left = 5;
PwmPin pwm_right = 8;

DigPin in_left_1 = 6;
DigPin in_left_2 = 7;
DigPin in_right_1 = 9;
DigPin in_right_2 = 10;

#endif