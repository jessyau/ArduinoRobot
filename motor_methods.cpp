#include "motor_methods.h"
#define lightThresh = 300

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

int correct_right( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 150, FORWARD );
    set_motor_state( right_motor, 90, FORWARD );
    delay(50);
    
    return 0;
}

int correct_left( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 90, FORWARD );
    set_motor_state( right_motor, 150, FORWARD );
    delay(50);
    
    return 0;
}

int drive_straight( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 120, FORWARD );
    set_motor_state( right_motor, 120, FORWARD );
    delay(50);
    
    return 0;
}

int stop_motors( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 0, FORWARD );
    set_motor_state( right_motor, 0, FORWARD );
    delay(50);
    
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
