#include<Wire.h>

void setup()
{
  Wire.begin();           // Join I2C bus (address optional for master).
  Serial.begin(9600);     // Start serial for output.

}

void loop()
{
  Wire.requestFrom(8,6);  // Request 6 bytes from peripheral device #8.

  while(Wire.available()) // Peripheral may send less than requested.
  {
    char c = Wire.read(); // Receive a byte as character.
    Serial.print(c);      // Print the character.
  }
  delay(500);

}
