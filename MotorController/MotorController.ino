#include <SoftwareSerial.h>

#include "PinConfig.h"
#include "ParamConfig.h"
#include "Command.h"
#include "Status.h"

#include "RemoteComm.h"
#include "EncoderComm.h"
#include "PID.h"

// SoftwareSerial bluetooth(9, 8); // BT(TX, RX)

RemoteComm remote_comm(Serial);  // replace with bluetooth
EncoderComm encoder_comm(Serial, cycle_time, n_pulses, gear_ratio);
PID pid[2] = {
  PID(cycle_time, kp, ki, kd, taud, limit_min, limit_max), 
  PID(cycle_time, kp, ki, kd, taud, limit_min, limit_max)
}; // one PID for each motor

void setup() {
  Serial.begin(9600);
  // bluetooth.begin(9600);  //uncomment

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
Status direction;

void loop() {
  // remote
  remote_comm.monitor();
  
  if (strcmp(remote_message, remote_comm.message) != 0) {
    strcpy(remote_message, remote_comm.message);

    setRPMSetpoint(remote_message);
  }

  // encoder
  encoder_comm.monitor();

  duty_cycle[0] = pid[0].getAction(rpm_setpoint[0], encoder_comm.rpm[0]);
  duty_cycle[1] = pid[1].getAction(rpm_setpoint[1], encoder_comm.rpm[1]);

  Serial.println(duty_cycle[0]);
  Serial.println(duty_cycle[1]);

  delay(1000);
}

void setRPMSetpoint(char *remote_message) {
  Command command = messageToCommand(remote_message);

  if (command == Command::FORWARD) {
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
  else return 0;
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
