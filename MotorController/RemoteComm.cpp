#include "RemoteComm.h"

RemoteComm::RemoteComm(HardwareSerial &port) : port(port) {}

void RemoteComm::monitor() {
    byte i = 0;
    char buffer[num_chars];
    bool done = false;

    while (port.available()) {
        char x = port.read();

        if (x == '!') {
            buffer[i] = '\0';
            strcpy(message, buffer);

            i = 0;
            done = true;
        } 
        else if (!done) {
            buffer[i] = x;

            i++;

            message[0] = '\0';
        }
    }
}