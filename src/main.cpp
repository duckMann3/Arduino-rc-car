#include <Arduino.h>

// Set Pins for Arduino-Uno Board:
#define enablePin_A 6
#define IN1 5
#define IN2 4
#define IN3 3
#define IN4 2
#define enablePin_B 1

// Set Pins & variables for Ultrasonic Sensor:
#define trigPin 13
#define echoPin 12
float duration, distance;

// Movement for DC Motor:
void motorA_forward();
void motorA_backward();
void motorB_forward();
void motorB_backward();

// Ultrasonic Sensor Read:
int ultrasonic_sensor();

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sets the pins as outputs:
  // pinMode(IN1, OUTPUT);
  // pinMode(IN2, OUTPUT);
  // pinMode(enablePin_A, OUTPUT);
  
  // pinMode(IN3, OUTPUT);
  // pinMode(IN4, OUTPUT);
  // pinMode(enablePin_B, OUTPUT);
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(enablePin_A, INPUT_PULLUP);
  
  pinMode(IN3, INPUT_PULLUP);
  pinMode(IN4, INPUT_PULLUP);
  pinMode(enablePin_B, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  // If there is an object distance 5.00 away from the ultrasonic sensor, move foward:
  if(ultrasonic_sensor() <= 5.00)
  {
    motorB_forward();
    // delayMicroseconds(10);
    motorA_forward();  
    delay(1000);
  }
  
  // Else don't move:
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(3000);
  }
}

int ultrasonic_sensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance); 
  delay(100);
  return distance;
}

void motorA_forward()
{
  Serial.println("Motor A: Move forward");
  analogWrite(enablePin_A, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorB_forward()
{
  Serial.println("Motor B: Move forward");
  analogWrite(enablePin_B, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void motorA_backward()
{
  Serial.println("Motor A: Move backward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
}

void motorB_backward()
{
  Serial.println("Motor B: Move backward");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
