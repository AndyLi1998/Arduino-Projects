#include <Servo.h>
Servo servo;
int angle = 0;
void setup() {
  servo.attach(8);
  servo.write(angle);
}
void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 0; angle < 90; angle++)  
  {                                  
    servo.write(angle);               
    delay(30);                   
  } 
  
}
