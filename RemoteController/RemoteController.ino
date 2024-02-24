#include <SoftwareSerial.h>

#include "PinDefs.h"
#include "Settings.h"

SoftwareSerial Bluetooth(tx, rx);

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void loop() {
  int x = analogRead(A0) / 4;
  int y = analogRead(A1) / 4;

  Serial.print('<');
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print('>');
  Serial.print('\n');
}
