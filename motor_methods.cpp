#include "motor_methods.h"
#include "line_sensors.h"

#define lightThresh 350

// Motor struct to store references to motor and motor encoder pins
int init_motor( struct dc_motor _new_motor ) {
    pinMode(_new_motor.dir_pin, OUTPUT);
    pinMode(_new_motor.pulse_pin, OUTPUT);

    digitalWrite(_new_motor.dir_pin, 0);
    analogWrite(_new_motor.pulse_pin, 0);

    return 0;
}

// Sets motor state to rotate at the referenced power in the specified direction
int set_motor_state( struct dc_motor motor, int power, enum directions dir ) {
    digitalWrite(motor.dir_pin, dir);
    analogWrite(motor.pulse_pin, power);

    return 0;
}

// Line corrects if robot is veering to the left
int correct_right( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 120, FORWARD );
    set_motor_state( right_motor, 70, FORWARD );
    delay(10);
    
    return 0;
}

// Line corrects if robot is veering to the right
int correct_left( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 70, FORWARD );
    set_motor_state( right_motor, 120, FORWARD );
    delay(10);
    
    return 0;
}

// Rotates both motors in same direction
int drive_straight( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 95, FORWARD );
    set_motor_state( right_motor, 100, FORWARD );
    delay(10);
    
    return 0;
}

// Stops motors
int stop_motors( struct dc_motor left_motor, struct dc_motor right_motor ) {
    set_motor_state( left_motor, 0, FORWARD );
    set_motor_state( right_motor, 0, FORWARD );
    delay(50);
    
    return 0;
}

// Makes a 90 degree left turn
int turn_left( struct dc_motor left_motor, struct dc_motor right_motor, int light_pin ) {
    drive_straight( left_motor, right_motor );
    
    delay(600);
  
    set_motor_state( left_motor, 95, BACKWARD );
    set_motor_state( right_motor, 100, FORWARD );
    
    while ( check_light( light_pin ) > lightThresh ) {
        delay(85);
    }
    
    drive_straight( left_motor, right_motor );
    
  
    return 0;
}

// Makes a 90 degree right turn
int turn_right( struct dc_motor left_motor, struct dc_motor right_motor, int light_pin ) {
    drive_straight( left_motor, right_motor );
    
    delay(600);
  
    set_motor_state( left_motor, 95, FORWARD );
    set_motor_state( right_motor, 100, BACKWARD );
    
    while ( check_light( light_pin ) > lightThresh ) {
        delay(80);
    }
    
    drive_straight( left_motor, right_motor );
    
    return 0;
}



// vim: ft=arduino :

