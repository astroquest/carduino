/*
Controls motors using RPM from encoder interface 
and PID to set the duty cycle in closed-loop
*/

#include "PinConfig.h"
#include "ParamConfig.h"

#include <Pid.h>
#include <EncoderInterfaceComm.h>

// instantiations
Pid pid_left(cycle_time, kp, ki, kd, taud, limit_min, limit_max);
Pid pid_right(cycle_time, kp, ki, kd, taud, limit_min, limit_max);

EncoderInterfaceComm eicomm_left(Serial1, cycle_time, n_pulses, gear_ratio, wheel_radius);
EncoderInterfaceComm eicomm_right(Serial1, cycle_time, n_pulses, gear_ratio, wheel_radius);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(pwm_left, OUTPUT);
  pinMode(pwm_right, OUTPUT);
  pinMode(in_left_1, OUTPUT);
  pinMode(in_left_2, OUTPUT);
  pinMode(in_right_1, OUTPUT);
  pinMode(in_right_2, OUTPUT);

  digitalWrite(in_left_1, LOW);
  digitalWrite(in_left_2, HIGH);
  digitalWrite(in_right_1, LOW);
  digitalWrite(in_right_2, HIGH);
}

double setpoint_left = 0;
double setpoint_right = 0;
double rpm_left = 0;
double rpm_right = 0;

double prev_duty_cycle_left = 0;
double prev_duty_cycle_right = 0;

void loop() {
  rpm_left = eicomm_left.getRpm();
  rpm_right = eicomm_left.getRpm();

  setPwm(pid_left, pwm_left, in_left_1, in_left_2, setpoint_left, rpm_left, prev_duty_cycle_left); // don't like having the prev duty cycle here, improve these functions
  setPwm(pid_right, pwm_right, in_right_1, in_right_2, setpoint_right, rpm_right, prev_duty_cycle_right); // not only setting the PWM but also direction, so function name is bad

  delay(cycle_time);
}

void setPwm(Pid pid, PwmPin pwm, DigPin in_1, DigPin in_2, double setpoint, double rpm, double prev_duty_cycle) {
  double duty_cycle = pid.getAction(setpoint, rpm);

  if (duty_cycle * prev_duty_cycle < 0) {
    switchDirection(in_1, in_2, duty_cycle);
  }

  prev_duty_cycle = duty_cycle;

  return analogWrite(pwm, round(abs(duty_cycle)*255));
}

void switchDirection(DigPin in_1, DigPin in_2, double duty_cycle) {
  if (duty_cycle < 0) {
    digitalWrite(in_1, HIGH);
    digitalWrite(in_2, LOW);
  }
  else {
    digitalWrite(in_1, LOW);
    digitalWrite(in_2, HIGH);
  }

}