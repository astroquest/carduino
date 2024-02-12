/*
    Handles communication with bluetooth-based remote controller
*/

#ifndef REMOTECOMM_H
#define REMOTECOMM_H

#include <Arduino.h>
#include <HardwareSerial.h>

class RemoteComm { // put this in a parent class
    public:
        RemoteComm(HardwareSerial &port);

        void monitor();

        static const int num_chars = 128;
        char message[num_chars];

    private:
        HardwareSerial &port;
};


#endif