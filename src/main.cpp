#include <Arduino.h>

// Set Pins for Joystick:
#define pinX A0
#define pinY A1
int click = 7;
int switchState = 0;
int xValue, yValue;

void setup()
{
  pinMode(click, INPUT);
  digitalWrite(click, HIGH);
  Serial.begin(9600);
}

void loop()
{
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  switchState = digitalRead(click);
  

  // Print output of Joystick: 
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print(" Button: ");
  Serial.println(switchState);
  
  delay(100);
}




