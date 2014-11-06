#ifndef motor_methods
#define motor_methods

#include <Arduino.h>

static const int LIGHT_ANA1_THRESH = 200;
static const int LIGHT_ANA2_THRESH = 200;
static const int LIGHT_ANA3_THRESH = 200;

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

int sample_grip_sensor();

#endif
