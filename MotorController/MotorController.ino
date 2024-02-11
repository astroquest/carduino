#include "PinConfig.h"
#include "ParamConfig.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(9, 8); // BT(TX, RX)

enum class Status {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  STOP,
  CHECK_VOLTAGE,
  INVALID
};

Status messageToStatus(char* message) {
  if (strcmp(message, "forward") == 0) {
    return Status::FORWARD;
  }
  else if (strcmp(message, "backward") == 0) {
    return Status::BACKWARD;
  }
  else if (strcmp(message, "left") == 0) {
    return Status::LEFT;
  }
  else if (strcmp(message, "right") == 0) {
    return Status::RIGHT;
  }
  else if (strcmp(message, "stop") == 0) {
    return Status::STOP;
  }
  else if (strcmp(message, "voltage") == 0) {
    return Status::CHECK_VOLTAGE;
  }
  else return Status::INVALID;
}

void setup() {
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

double duty_cycle[2] = {0, 0};
Status direction;

void loop() {
  byte i = 0;
  char buffer[num_chars];
  bool done = false;

  while (bluetooth.available()) {
    char x = bluetooth.read();

    if (x == '!') {
      buffer[i] = '\0';

      Status status = messageToStatus(buffer);

      if (status == Status::FORWARD) {
        if (direction == Status::BACKWARD) {
          setMotorsForward();
        }

        duty_cycle[0] = 120;
        duty_cycle[1] = 100;
      }
      else if (status == Status::BACKWARD) {
        if (direction == Status::FORWARD) {
          setMotorsBackward();
        }

        duty_cycle[0] = 80;
        duty_cycle[1] = 70;
      }
      else if (status == Status::LEFT) {
        duty_cycle[0] = 80;
        duty_cycle[1] = 140;
      }
      else if (status == Status::RIGHT) {
        duty_cycle[0] = 140;
        duty_cycle[1] = 80;
      }
      else if (status == Status::STOP) {
        duty_cycle[0] = 0;
        duty_cycle[1] = 0;
      }
      else if (status == Status::CHECK_VOLTAGE) {
        // check battery voltage
      }

      i = 0;
      done = true;
    } 
    else if (done == false){
      buffer[i] = x;

      i++;
    }
  }

  for (int i = 0; i < 2; i++) {
    analogWrite(pwm_pins[i], duty_cycle[i]);
  }
  
  delay(cycle_time);
}

void setMotorsForward() {
  digitalWrite(enable_pins[0], LOW);
  digitalWrite(enable_pins[1], HIGH);
  digitalWrite(enable_pins[2], LOW);
  digitalWrite(enable_pins[3], HIGH);

  direction = Status::FORWARD;
}

void setMotorsBackward() {
  digitalWrite(enable_pins[0], HIGH);
  digitalWrite(enable_pins[1], LOW);
  digitalWrite(enable_pins[2], HIGH);
  digitalWrite(enable_pins[3], LOW);

  direction = Status::BACKWARD;
}
