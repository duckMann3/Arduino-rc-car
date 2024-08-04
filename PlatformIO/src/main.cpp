#include <Arduino.h>
// Set Pins for Arduino-Uno Board
#define enablePin_A 6
#define IN1 5
#define IN2 4
#define IN3 3
#define IN4 2
#define enablePin_B 1

#define trigPin 13
#define echoPin 12

// Set Pins for 
float duration, distance;

void motorA_forward();
void motorA_backward();
void motorB_forward();
void motorB_backward();
int ultrasonic_sensor();

void setup()
{

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sets the pins as outputs:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(enablePin_A, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enablePin_B, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  int dist = ultrasonic_sensor();

  if(dist <= 5.00)
  {
    motorA_forward();  
    delayMicroseconds(500);
    motorB_forward();
    delay(500);
  }

  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(500);
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
  Serial.println("Motor A: forward");
  analogWrite(enablePin_A, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorB_forward()
{
  Serial.println("Motor B: Motor forward");
  analogWrite(enablePin_B, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void motorA_backward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
}

void motorB_backward()
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
