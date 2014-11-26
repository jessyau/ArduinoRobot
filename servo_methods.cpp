#include "servo_methods.h"
#include <Servo.h>

// Drops marble/"radiation dose" into target if positioned to the left of robot
int erradicate_left( Servo servo_base, Servo servo_grip ) {
    servo_base.write(85);
    
    delay(300);
    
    servo_grip.write(80);
    delay(150);
    servo_grip.write(160);
    
  return 0;

}

// Drops marble/"radiation dose" into target if positioned to the right of robot
int erradicate_right( Servo servo_base, Servo servo_grip ) {
    servo_base.write(130);
    
    delay(300);
    
    servo_grip.write(80);
    delay(150);
    servo_grip.write(160);
    
  return 0;
  
}

// Samples values from grip sensor
int sample_grip_sensor() {
    pinMode(A0, OUTPUT);
    digitalWrite(A0, LOW);
    delayMicroseconds(10);
    pinMode(A0, INPUT);

    return analogRead(A0);
}
