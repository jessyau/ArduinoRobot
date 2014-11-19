#include <Servo.h>
#include "motor_methods.h"
//#include "line_sensors.h"
//#include "servo_methods.h"
//#include "target_methods.h"

#define lightThresh 250

//Pin definitions
static const int RED_LED = 13;
//static const int YELLOW_LED = 3;
//static const int GREEN_LED = 3;

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

struct dc_motor drive_motors[2];
//struct line_tracker track_light[3];

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
    
    pinMode(LIGHT_LEFT, INPUT);
    pinMode(LIGHT_MID, INPUT);
    pinMode(LIGHT_RIGHT, INPUT);
    
    pinMode(RED_LED, OUTPUT);
    
}

void loop() {
  
   drive();
   //delay(50);
   //grab_ball();
        
   while(1) {}
   
//   Serial.println(check_right_light());
//   Serial.flush();
//   delay(500);
  
}

int check_left_light() {
  return analogRead(LIGHT_LEFT);
}

int check_mid_light() {
  return analogRead(LIGHT_MID);
}

int check_right_light() {
  return analogRead(LIGHT_RIGHT);
}

void check_motors() {
    digitalWrite(MOTOR_M1, LOW);
    analogWrite(MOTOR_E1, 100);

    digitalWrite(MOTOR_M2, LOW);
    analogWrite(MOTOR_E2, 100);

    delay(1000);

    return;
}

void check_bumpers() {
    Serial.print("Value left bumper: ");
    Serial.println(digitalRead(BUMP_LEFT));

    Serial.print("Value right bumper: ");
    Serial.println(digitalRead(BUMP_RIGHT));

    return;
}

void check_grip() {
    Serial.println(sample_grip_sensor());
    
    return;
}

void check_ir() {
    while(Serial.available() <= 0) delay( 100 );
    Serial.println(Serial.read());
    Serial.flush();
}

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


void drive() {
  int light_right = analogRead(LIGHT_RIGHT);
  //int light_mid = analogRead(LIGHT_MID);
  int light_left = analogRead(LIGHT_LEFT);
  
//  drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
//  
 while( check_left_light() >= lightThresh || check_right_light() >= lightThresh ) {
    
      if( check_right_light() < lightThresh ) {
          correct_right( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
       }else if(check_left_light() < lightThresh) {
          correct_left( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
       }else{
          drive_straight( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
       }   
}  
  if(check_left_light() < lightThresh && check_right_light() < lightThresh ) {
             stop_motors( drive_motors[LEFT_MOTOR], drive_motors[RIGHT_MOTOR] );
   
   }
  
}
