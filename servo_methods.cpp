#include "servo_methods.h"
#include <Servo.h>

int erradicate_left( Servo servo_base, Servo servo_grip ) {
    servo_base.write(85);
    
    delay(300);
    
    servo_grip.write(50);
    delay(80);
    servo_grip.write(110);
    
  return 0;

}

int erradicate_right( Servo servo_base, Servo servo_grip ) {
    servo_base.write(130);
    
    delay(300);
    
    servo_grip.write(50);
    delay(80);
    servo_grip.write(110);
    
  return 0;
  
}

