#ifndef motor_methods
#define motor_methods

#include <Arduino.h>

struct dc_motor {
    int dir_pin;
    int pulse_pin;
};

enum {
    LEFT_MOTOR,
    RIGHT_MOTOR
};

enum directions {
    BACKWARD,
    FORWARD
};

int init_motor( struct dc_motor );
int set_motor_state( struct dc_motor, int, enum directions );
int correct_right( struct dc_motor, struct dc_motor );
int correct_left( struct dc_motor, struct dc_motor );
int drive_straight( struct dc_motor, struct dc_motor );
int stop_motors( struct dc_motor, struct dc_motor );
int turn_left( struct dc_motor, struct dc_motor, int );
int turn_right( struct dc_motor, struct dc_motor, int );

#endif
