#include <Arduino.h>

// Set Pin Macros for Motor Driver: 
#define enablePin_A 6
#define IN1 5
#define IN2 4
#define IN3 3
#define IN4 2
#define enablePin_B 1

void setup()
{

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sets the pins as outputs:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(enablePin_A, OUTPUT);
  pinMode(enablePin_B, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Control Speed (PWM) (0-255)
  analogWrite(enablePin_A, 200);
  analogWrite(enablePin_B, 100);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3000);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(3000);
}
