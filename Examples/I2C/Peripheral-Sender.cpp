#include<Arduino.h>
#include<Wire.h>

void requestEvent();

void setup()
{
  Wire.begin(8);                // Join I2C bus with address #8
  Wire.onRequest(requestEvent); // Register event
}

void loop()
{
  delay(100);
}

// Function that executes whatever data is requested by master
// thus function is registered as an event
void requestEvent()
{
  Wire.write("hello "); // respond with message of 6 bytes
                        // as expected by master
}


