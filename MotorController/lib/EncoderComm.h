/*
    Handles communication with encoder interface
*/

#ifndef ENCODERCOMM_H
#define ENCODERCOMM_H

#include <Arduino.h>
#include <HardwareSerial.h>

class EncoderComm {
    public:
        EncoderComm(HardwareSerial &port, double, int, double);

        void monitor();

        double rpm[2];

        static const int num_chars = 128;
        char message[num_chars];

    private:
        void init(int, double);
        double computeRPM(long, long);

        HardwareSerial &port;

        double rpm_conversion_factor;
        long count[2];
        long prev_count[2];

        double cycle_time;
};

#endif