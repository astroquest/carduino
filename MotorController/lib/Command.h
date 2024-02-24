#ifndef COMMAND_H
#define COMMAND_H

/*
    Enum and associated string definitions of recognized Commands
*/

enum class Command {
    FORWARD,
    REVERSE,
    LEFT,
    RIGHT,
    STOP,
    CHECK_VOLTAGE,
    INVALID
};

Command messageToCommand(char* message) {
    if (strcmp(message, "forward") == 0) {
        return Command::FORWARD;
    }
    else if (strcmp(message, "reverse") == 0) {
        return Command::REVERSE;
    }
    else if (strcmp(message, "left") == 0) {
        return Command::LEFT;
    }
    else if (strcmp(message, "right") == 0) {
        return Command::RIGHT;
    }
    else if (strcmp(message, "stop") == 0) {
        return Command::STOP;
    }
    else if (strcmp(message, "voltage") == 0) {
        return Command::CHECK_VOLTAGE;
    }
    else return Command::INVALID;
}

#endif