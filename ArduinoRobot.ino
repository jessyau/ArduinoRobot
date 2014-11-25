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
//    target_list.row[5] = { 0 0 0 0 0 };
//    target_list.col[5] = { 0, 0, 0, 0, 0 };
    
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED2_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    
}

void loop() {
    
      
//    while( turn_count < 7 ) {
//       destroy_shit();
//     
//    }

    erradicate_right( servo_base, servo_grip );
    delay(2000);

    //while(1){};
//     
//     Serial.println(check_light(LIGHT_RIGHT));
//     Serial.flush();
//     delay(200);
//   
  
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
void destroy_shit() {
  while( check_light(LIGHT_LEFT) > lightThresh || check_light(LIGHT_RIGHT) > lightThresh ) {
    if( check_light(LIGHT_LEFT) < lightThresh ) {
//      if( is_left_target( light_sensor ) && !(is_turn( light_sensor))) {
//         Serial.println("left target");
//           stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//           radiate_begin();
//           erradicate_left( servo_base, servo_grip );
//           radiate_end();
//           drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//           delay(300);
//       } else {
           correct_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//       }
    } else if( check_light(LIGHT_RIGHT) < lightThresh ) {
//        if( is_right_target( light_sensor && !(is_turn( light_sensor))) ) {
//           Serial.println("right target");
//             stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//             radiate_begin();
//             erradicate_right( servo_base, servo_grip );
//             radiate_end();
//             drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//             delay(300);
//         } else {
             correct_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//         }
    } else if( check_light( LIGHT_MID ) > lightThresh && check_light( LIGHT_LEFT ) > lightThresh && check_light( LIGHT_RIGHT ) > lightThresh){
        track_position( target_list, turn_count, is_left_target( light_sensor ), is_right_target( light_sensor ) );
        delay(270);
    }
    else {
        drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
    }
    
  }
  
 // Checks for markers for a turn and turns a certain direction based on count
 // Left turns for the first 3 turns, Right turns for the next 3
  if( is_turn( light_sensor ) ) {
     turn_count++;
     Serial.print("Turn count: ");
     Serial.println( turn_count );
     
     if( turn_count <= 3 ) {
       Serial.println("turn left");
       turn_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else if( turn_count <= 6 ) {
       Serial.println("turn right");
       turn_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR], LIGHT_MID );
     } else 
       Serial.println("stop here");
       stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
  }
  
}
