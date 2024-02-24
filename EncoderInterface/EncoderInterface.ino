/* 
  Converts encoder readings to counts 
  and sends counts over serial communication when prompted.
*/ 

#include <Encoder.h>

#include "PinDefs.h"
#include "Settings.h"

Encoder encoders[2] {
  Encoder(encoder_pins_left[0], encoder_pins_left[1]), // 2 and 3 are external interrupt pins on the arduino uno
  Encoder(encoder_pins_right[0], encoder_pins_right[1])
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 2; i++) {
    counts[i] = encoders[i].read();
  }

  sendCountsOnRequest(counts);
}

void sendCountsOnRequest(long *counts) {
  /*
    If main mcu sends a 0 char, 
    the encoder interface will respond with the current counts.
  */

  if (Serial.available() > 0 && Serial.read() == '0') {
      Serial.print(counts[0]);
      Serial.write(',');
      Serial.print(counts[1]);
      Serial.write("!");
      Serial.write("\n");
  }
}
