/*
parameter definitions
*/

#ifndef SETTINGS_H
#define SETTINGS_H

const int n_motors = 2;

const double cycle_time = 0.1;
const double sampling_rate = 10;
const double sampling_time = 1 / sampling_rate;

// encoder settings
const int n_pulses = 11;
const double gear_ratio = 56;
const double wheel_radius = 0.3;

// motor controller settings
const double kp = 0.01;
const double ki = 0.01;
const double kd = 0;
const double tau = 0;
const double limit_min = 0;
const double limit_max = 0.3;

PIDParams pid_params {kp, ki, kd, tau, limit_min, limit_max};

// bluetooth message settings
static const byte num_chars = 128;

#endif