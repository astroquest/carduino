#include <SoftwareSerial.h>

#include "PinConfig.h"
#include "ParamConfig.h"
#include "Status.h"

#include "RemoteComm.h"

// SoftwareSerial bluetooth(9, 8); // BT(TX, RX)

void setup() {
  Serial.begin(9600);
  // bluetooth.begin(9600);

  // for (int i = 0; i < 2; i++) {
  //   pinMode(pwm_pins[i], OUTPUT);
  // }

  // for (int i = 0; i < 4; i++) {
  //   pinMode(enable_pins[i], OUTPUT);
  // }

  // digitalWrite(enable_pins[0], LOW);
  // digitalWrite(enable_pins[1], HIGH);
  // digitalWrite(enable_pins[2], LOW);
  // digitalWrite(enable_pins[3], HIGH);
}

RemoteComm remote_comm(Serial);  // replace with bluetooth

char remote_message[num_chars];

void loop() {
  remote_comm.monitor();
  
  if (strcmp(remote_message, remote_comm.message) != 0) {
    strcpy(remote_message, remote_comm.message);

    Serial.println(remote_message);
  }
  
  delay(1000);
}

// void setMotorsForward() {
//   digitalWrite(enable_pins[0], LOW);
//   digitalWrite(enable_pins[1], HIGH);
//   digitalWrite(enable_pins[2], LOW);
//   digitalWrite(enable_pins[3], HIGH);

//   direction = Status::FORWARD;
// }

// void setMotorsBackward() {
//   digitalWrite(enable_pins[0], HIGH);
//   digitalWrite(enable_pins[1], LOW);
//   digitalWrite(enable_pins[2], HIGH);
//   digitalWrite(enable_pins[3], LOW);

//   direction = Status::BACKWARD;
// }
