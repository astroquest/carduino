/*
    definition of pinouts
*/

#ifndef PINDEFS_H
#define PINDEFS_H

typedef const int Pin;

Pin pwm_left = 5;
Pin pwm_right = 3;
Pin en_left_1 = 7;
Pin en_left_2 = 6;
Pin en_right_1 = 11;
Pin en_right_2 = 10;
Pin tx = 9;
Pin rx = 8;


Pin pwm_pins[2] = {pwm_left, pwm_right};
Pin enable_pins[4] = {en_left_1, en_left_2, en_right_1, en_right_2};

#endif