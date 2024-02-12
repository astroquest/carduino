#include "EncoderComm.h"

EncoderComm::EncoderComm(
        HardwareSerial &port,
        double cycle_time,
        int n_pulses,
        double gear_ratio
    ) : port(port), cycle_time(cycle_time) {

    init(n_pulses, gear_ratio);
}

void EncoderComm::init(int n_pulses, double gear_ratio) {
    double counts_per_rotation = (n_pulses * gear_ratio * 4);  // assumes 4X counting
    rpm_conversion_factor = 60.0 / counts_per_rotation * 1000;

    prev_count[0] = 0;
    prev_count[1] = 0;
}

void EncoderComm::monitor() {
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

    if (done) {
        char* ptr_token;
        ptr_token = strtok(message, ",");

        count[0] = atol(ptr_token);
        // port.println(count[0]);

        ptr_token = strtok(NULL, ",");
        count[1] = atol(ptr_token);
        // port.println(count[1]);

        rpm[0] = computeRPM(count[0], prev_count[0]);
        prev_count[0] = count[0];

        rpm[1] = computeRPM(count[1], prev_count[1]);
        prev_count[1] = count[1];
    }
}

double EncoderComm::computeRPM(long val, long prev_val) {
    return (val - prev_val) / cycle_time * rpm_conversion_factor;
}