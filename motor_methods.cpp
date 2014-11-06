#include "motor_methods.h"

int init_motor( struct dc_motor _new_motor ) {
    pinMode(_new_motor.dir_pin, OUTPUT);
    pinMode(_new_motor.pulse_pin, OUTPUT);

    digitalWrite(_new_motor.dir_pin, 0);
    analogWrite(_new_motor.pulse_pin, 0);

    return 0;
}

int set_motor_state( struct dc_motor motor, int power, enum directions dir ) {
    digitalWrite(motor.dir_pin, dir);
    analogWrite(motor.pulse_pin, power);

    return 0;
}

int sample_grip_sensor() {
    pinMode(A0, OUTPUT);
    digitalWrite(A0, LOW);
    delayMicroseconds(10);
    pinMode(A0, INPUT);

    return analogRead(A0);
}

// vim: ft=arduino :
