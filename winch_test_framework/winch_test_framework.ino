#include <A4990MotorShield.h>

#include "Arduino.h"

char message;
A4990MotorShield motors;

void setup()
{
  Serial.begin(9600); 
}

void loop()
{   
  if (Serial.available())
  {
    message = Serial.read();
    Serial.println(message);
    if (message == '1')
    {
      motors.setM2Speed(100);
    }  
    else if (message == '2')
    {
      motors.setM2Speed(-100);
    }
    else {
      motors.setM2Speed(0);
    }
  }
  delay(500);
}
