#include <Servo.h>
#include "motor_methods.h"
//#include "QSerial.h"

#define lightThresh 300

//Pin definitions
static const int IR_RECEIVER = 0; 

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

static const int LIGHT_ANA1_LEFT  = A3;
static const int LIGHT_ANA2_MID   = A4;
static const int LIGHT_ANA3_RIGHT = A5;

//QSerial irs;

Servo servo_base;
Servo servo_tilt;
Servo servo_grip;

struct dc_motor drive_motors[2];
directions dir;

void setup() {
    Serial.begin( 9600 );
    
    //irs.attach(0, -1);
    
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

    servo_base.write(105);
    servo_tilt.write(160);
    servo_grip.write(50);
    
    pinMode(LIGHT_ANA1_LEFT, INPUT);
    pinMode(LIGHT_ANA2_MID, INPUT);
    pinMode(LIGHT_ANA3_RIGHT, INPUT);
    
}

void loop() {
 // check_motors();
  
 // check_light();
//  delay(100);
//  
  //check_bumpers();
 //delay(1000);
//
// check_grip();
    delay(2000);
  
   drive();
   delay(50);
   grab_ball();
  
}

void check_light() {
  while(Serial.available() <= 0 ) {
    Serial.print("LIGHT_LEFT:  ");
    Serial.println(analogRead(LIGHT_ANA1_LEFT));
  }
//    Serial.print("LIGHT_MID:   ");
//    Serial.println(analogRead(LIGHT_ANA2_MID));
//
//    Serial.print("LIGHT_RIGHT: ");
//    Serial.println(analogRead(LIGHT_ANA3_RIGHT));
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
 // while(Serial.available)()
  //{
    Serial.print("Value left bumper: ");
    Serial.println(digitalRead(BUMP_LEFT));

    Serial.print("Value right bumper: ");
    Serial.println(digitalRead(BUMP_RIGHT));
 // }
    return;
}

void check_grip() {
    Serial.println(sample_grip_sensor());
    
    return;
}

void check_ir() {
    while(Serial.available() <= 0) delay(100);
    Serial.println(Serial.read());
    Serial.flush();
}

void grab_ball() {
    servo_base.write(15);
    delay(1000);
    servo_tilt.write(100);
    
    
    int gripThresh = sample_grip_sensor();
    int gripPos = 50;
    
    while(gripThresh <= 400) {
     gripPos++;
     servo_grip.write(gripPos);
     delay(50);
     gripThresh = sample_grip_sensor();
    }
    
    
    servo_tilt.write(160);
    servo_base.write(105);
    delay(1000);
    servo_grip.write(50);
    
}


void drive() {
  int light_right = analogRead(LIGHT_ANA3_RIGHT);
  int light_mid = analogRead(LIGHT_ANA2_MID);
  int light_left = analogRead(LIGHT_ANA1_LEFT);
  
  set_motor_state( drive_motors[LEFT_MOTOR], 120, FORWARD );
  set_motor_state( drive_motors[RIGHT_MOTOR], 120, FORWARD );
  
  while( light_right >= lightThresh || light_mid >= lightThresh || light_left >= lightThresh) {
      light_right = analogRead(LIGHT_ANA3_RIGHT);
      light_mid = analogRead(LIGHT_ANA2_MID);
      light_left = analogRead(LIGHT_ANA1_LEFT);
      
      set_motor_state( drive_motors[LEFT_MOTOR], 100, FORWARD );
      set_motor_state( drive_motors[RIGHT_MOTOR], 100, FORWARD );
  }
  
  set_motor_state( drive_motors[LEFT_MOTOR], 0, FORWARD );
  set_motor_state( drive_motors[RIGHT_MOTOR], 0, FORWARD );
  
}
