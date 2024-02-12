/* 
  Converts encoder readings to counts 
  and sends counts over serial communication when prompted.
*/ 

#include <Encoder.h>

Encoder encoders[2] {
  Encoder(2, 12), // 2 and 3 are external interrupt pins on the arduino uno
  Encoder(3, 11)
};

void setup() {
  Serial.begin(9600);

  // pinMode(6, INPUT);
}

long counts[2] {0, 0};

void loop() {
  for (int i = 0; i < 2; i++) {
    counts[i] = encoders[i].read();
  }

  sendCountsOnRequest(counts);
}

void sendCountsOnRequest(long *counts) {
  if (Serial.available() > 0 && Serial.read() == '0') {
      Serial.print(counts[0]);
      Serial.write(',');
      Serial.print(counts[1]);
      Serial.write("!");
      Serial.write("\n");
  }
}
