/* 
Converts encoder readings to counts 
and sends counts over serial communication when asked.
*/ 

#include <Encoder.h>

Encoder encoder_left(2, 4);  // 2 and 3 are external interrupt pins on the arduino uno
Encoder encoder_right(3, 5);

void setup() {
  Serial.begin(9600);
}

long prev_count_left = -999;
long prev_count_right = -999;
char buffer[12];

void loop() {
  long count_left = encoder_left.read();
  long count_right = encoder_right.read();

  updateCount(count_left, prev_count_left);
  updateCount(count_right, prev_count_right);

  sendCountsOnRequest(count_left, count_right);
}

void updateCount(long count, long prev_count) {
  if (count != prev_count) {
    prev_count = count;
  }  
}

void sendCountsOnRequest(long count_left, long count_right) {
  if (Serial.available() > 0 && Serial.read() == '0') {
      writeMessage(count_left);
      writeMessage(count_right);
      Serial.write("\n");
  }
}

void writeMessage(long count) {
  Serial.write(ltoa(count, buffer, 10));
  Serial.write(",");  
}
