#include <Servo.h>
#include "motor_methods.h"
#include "line_sensors.h"
#include "servo_methods.h"
#include "target_methods.h"

#define lightThresh 350

//Pin definitions
static const int RED_LED = 13;
static const int RED2_LED = 3;
static const int GREEN_LED = 2;

static const int SERVO_BASE = 11;
static const int SERVO_TILT = 10;
static const int SERVO_GRIP = 9;

static const int BUMP_LEFT = 3;
static const int BUMP_RIGHT = 2;

static const int MOTOR_M1 = 4;
static const int MOTOR_E1 = 5;

static const int MOTOR_M2 = 7;
static const int MOTOR_E2 = 6;

static const int MOTOR_ENC_LEFT = 8;
static const int MOTOR_ENC_RIGHT = 12;

static const int LIGHT_LEFT  = A2;
static const int LIGHT_MID   = A3;
static const int LIGHT_RIGHT = A4;

Servo servo_base;
Servo servo_tilt;
Servo servo_grip;

int turn_count = 0;
int target_count = 0;

struct dc_motor drive_motors[2];
struct line_tracker light_sensor;
struct target target_list;

void setup() {
    Serial.begin( 9600 );
        
    drive_motors[LEFT_MOTOR].dir_pin = MOTOR_M1;
    drive_motors[LEFT_MOTOR].pulse_pin = MOTOR_E1;

    drive_motors[RIGHT_MOTOR].dir_pin = MOTOR_M2;
    drive_motors[RIGHT_MOTOR].pulse_pin = MOTOR_E2;
    
    init_motor(drive_motors[LEFT_MOTOR]);
    init_motor(drive_motors[RIGHT_MOTOR]);

    pinMode(A0, INPUT);
    digitalWrite(A0, LOW);

    servo_base.attach(SERVO_BASE);
    servo_tilt.attach(SERVO_TILT);
    servo_grip.attach(SERVO_GRIP);
    
    servo_grip.write(160);
    
    light_sensor.left_pin = LIGHT_LEFT;
    light_sensor.mid_pin = LIGHT_MID;
    light_sensor.right_pin = LIGHT_RIGHT;
    
    init_lineTracker( light_sensor );
    
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED2_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    
}

// Frame loop carries out the main execution of code
void loop() {
    
    while( get_col() < 16 ) {
       destroy();
    }

    while(1){};
}

//Turn on Red LEDs to signal the beginning of "tuberculosis treatment"
void radiate_begin() {
   digitalWrite(RED2_LED, HIGH);
   digitalWrite(RED_LED, HIGH);
   delay(1000);
}

//Turns off Red LEDS and turns on Green LEDS to signal the end of "tuberculosis treatment"
void radiate_end() {
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(RED2_LED, LOW);
   digitalWrite(RED_LED, LOW);
   delay(1000);
   digitalWrite(GREEN_LED, LOW); 
}

// Target elimination method
void eliminate_target() {
   track_target( target_list, target_count );
   target_count++;
   stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
   radiate_begin();
   erradicate_right( servo_base, servo_grip );
   delay(1000);
   erradicate_left( servo_base, servo_grip );
   radiate_end();
}

// Target elimination to the right
void eliminate_right() {
   track_target( target_list, target_count );
   target_count++;
   stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
   radiate_begin();
   erradicate_right( servo_base, servo_grip );
   radiate_end();
}

// For progress report 1 demonstration -- grabs a ball with servo arm and releases it
void grab_ball() {
    servo_base.write( 15 );
    delay( 1000 );
    servo_tilt.write( 100 );
    
    
    int gripThresh = sample_grip_sensor();
    int gripPos = 50;
    
    while( gripThresh <= 400 ) {
     gripPos++;
     servo_grip.write( gripPos );
     delay( 50 );
     gripThresh = sample_grip_sensor();
    }
    
    servo_tilt.write( 160 );
    servo_base.write( 105 );
    delay( 1000 );
    servo_grip.write( 50 );
    
}

// Conditional statements dictate whether to line correct left or right or track position in map
void destroy() {
  while( check_light(LIGHT_LEFT) > lightThresh || check_light(LIGHT_RIGHT) > lightThresh ) {
    if( check_light(LIGHT_LEFT) < lightThresh ) {
           correct_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
    } else if( check_light(LIGHT_RIGHT) < lightThresh ) {
           correct_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
    } else if( check_light( LIGHT_MID ) > lightThresh && check_light( LIGHT_LEFT ) > lightThresh && check_light( LIGHT_RIGHT ) > lightThresh){
        track_position( );
        delay(270);
    }
    else {
        drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
    }
  }
  
 // Checks for markers for a turn and turns a certain direction based on count
 // Left turns for the first 3 turns, Right turns for the next 3
 // Also checks for when to dispense "radiation" and dispenses it
  if( is_turn( light_sensor ) ) {
     if( get_col() == 0 && turn_count == 0) {
         turn_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
         turn_count++;
     } else if( get_col() == 5 && turn_count == 1 ) {
         turn_count++;
         turn_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( get_col() == 5 && turn_count == 2 ) {
       turn_count++;
       turn_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( get_col() == 10 && turn_count == 3 ) {
       turn_count++;
       turn_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( get_col() == 10 && turn_count == 4 ) {
       turn_count++;
       turn_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( get_col() > 14 && turn_count == 5 ) {
       turn_count++; 
       turn_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( get_col() > 14 && turn_count == 6 ) {
       stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
     } else if( get_col() > 10 ) {
       eliminate_right();
       drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
       delay(300);
     } else {
       eliminate_target();
       drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
       delay(300);
     }
  }
  
}
