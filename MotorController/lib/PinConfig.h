/*
definition of pinouts
*/

#ifndef PINCONFIG_H
#define PINCONFIG_H

typedef const int EnablePin;
typedef const int PWMPin;

PWMPin pwm_left = 5;
PWMPin pwm_right = 3;
EnablePin en_left_1 = 7;
EnablePin en_left_2 = 6;
EnablePin en_right_1 = 11;
EnablePin en_right_2 = 10;

PWMPin pwm_pins[2] = {pwm_left, pwm_right};
EnablePin enable_pins[4] = {en_left_1, en_left_2, en_right_1, en_right_2};

#endif