/*
parameter definitions
*/

const int n_motors = 2;

const double cycle_time = 100;

// encoder settings
const int n_pulses = 11;
const double gear_ratio = 56;
const double wheel_radius = 0.3;

// motor controller settings
const double kp = 0.01;
const double ki = 0.01;
const double kd = 0;
const double taud = 0;
const double limit_min = 0;
const double limit_max = 0.3;

// bluetooth message settings
static const byte num_chars = 128;