#include <SoftwareSerial.h>

#include "lib/RemoteComm.h"
#include "lib/EncoderComm.h"
#include "lib/PID.h"

#include "lib/PinConfig.h"
#include "lib/ParamConfig.h"
#include "lib/Command.h"
#include "lib/Status.h"

SoftwareSerial bluetooth(9, 8); // BT(TX, RX)

RemoteComm remote_comm(bluetooth);
EncoderComm encoder_comm(Serial, cycle_time, n_pulses, gear_ratio);
PID pid[2] = {
  PID(cycle_time, pid_params), 
  PID(cycle_time, pid_params)
}; // one PID for each motor

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  for (int i = 0; i < 2; i++) {
    pinMode(pwm_pins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(enable_pins[i], OUTPUT);
  }

  digitalWrite(enable_pins[0], LOW);
  digitalWrite(enable_pins[1], HIGH);
  digitalWrite(enable_pins[2], LOW);
  digitalWrite(enable_pins[3], HIGH);
}

char remote_message[num_chars];
double rpm_setpoint[2] {0,0};
double duty_cycle[2] {0,0};
Status direction = Status::FORWARD;

void loop() {
  // remote
  remote_comm.monitor();
  
  if (strcmp(remote_message, remote_comm.message) != 0) {
    strcpy(remote_message, remote_comm.message);

    setRPMSetpoint(remote_message);
  }

  // encoder
  encoder_comm.monitor();

  for (int i = 0; i < 2; i++) {
    duty_cycle[i] = pid[i].getAction(rpm_setpoint[i], encoder_comm.rpm[i]);
    int duty_cycle_analog = abs(round(duty_cycle[i] * 255));

    if (rpm_setpoint[i] == 0.0) { // fix this case
      analogWrite(pwm_pins[i], 0);
    }
    else {
      analogWrite(pwm_pins[i], duty_cycle_analog);
    }
  }

  delay(cycle_time);
}

void setRPMSetpoint(char *remote_message) { // overloaded function, bad name
  Command command = messageToCommand(remote_message);

  if (command == Command::FORWARD) { // doesn't work correctly for left motor
    if (direction == Status::REVERSE) {
      setMotorsForward();
    }

    rpm_setpoint[0] = 50;
    rpm_setpoint[1] = 50;
  }
  else if (command == Command::REVERSE) {
    if (direction == Status::FORWARD) {
      setMotorsReverse();
    }

    rpm_setpoint[0] = 50;
    rpm_setpoint[1] = 50;
  }
  else if (command == Command::LEFT) {
    rpm_setpoint[0] = 45;
    rpm_setpoint[1] = 55;
  }
  else if (command == Command::RIGHT) {
    rpm_setpoint[0] = 55;
    rpm_setpoint[1] = 45;
  }
  else if (command == Command::STOP) {
    rpm_setpoint[0] = 0;
    rpm_setpoint[1] = 0;
  }
}

void setMotorsForward() {
  digitalWrite(enable_pins[0], LOW);
  digitalWrite(enable_pins[1], HIGH);
  digitalWrite(enable_pins[2], LOW);
  digitalWrite(enable_pins[3], HIGH);

  direction = Status::FORWARD;
}

void setMotorsReverse() {
  digitalWrite(enable_pins[0], HIGH);
  digitalWrite(enable_pins[1], LOW);
  digitalWrite(enable_pins[2], HIGH);
  digitalWrite(enable_pins[3], LOW);

  direction = Status::REVERSE;
}
