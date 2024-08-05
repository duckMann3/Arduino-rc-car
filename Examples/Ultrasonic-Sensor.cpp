#include <Arduino>
#define trigPin 13
#define echPin 12

float distance, duration;

void setup()
{
  pinMode(trigPin, OUPUT);
  pinModde(echo, INPUT);

  Serial.begin(9600);
}


void loop()
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

}
