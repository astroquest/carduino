#ifndef STATUS_H
#define STATUS_H

/*
    Enum and associated string definitions of recognized statuses
*/

enum class Status {
    FORWARD,
    REVERSE,
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
    else if (strcmp(message, "reverse") == 0) {
        return Status::REVERSE;
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

#endif