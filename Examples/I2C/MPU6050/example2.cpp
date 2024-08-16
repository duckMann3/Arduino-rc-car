#include<Arduino.h>
#include<Wire.h>

#define MPU_address 0x68
double pitch_input, roll_input, yaw_input, altitude_input;
double xAcc, yAcc, zAcc, xGyro, zGyro;
double current_gyroMillis, previous_gyroMillis, delta_gyroTime;
double pitch_inputAcc, roll_inputAcc, yaw_inputAcc;
double pitch_inputGyro, roll_inputGyro, yaw_inputGyro;
double rolly_gyroOffset, pitch_gyroOffset, yaw_gyroOffset, roll_accOffset, ptich_accOffset, yaw_accOffset;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_address);
  Wire.write(0x68);
  Wire.write(0);
  Wire.endTransmission(true);

  // Gyro Config:
  Wire.beginTransmission(MPU_address);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission(true);
  current_gyroMillis = millis();
  if(roll_accOffset == 0)
  {
    for(int i = 0; i < 200; i++)
    {
      Wire.beginTransmission(MPU_address);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_address, 6, true);

      xAcc = (Wire.read() << 8 | Wire.read()) / 4096.0; 
      yAcc = (Wire.read() << 8 | Wire.read()) / 4096.0; 
      zAcc = (Wire.read() << 8 | Wire.read()) / 4096.0; 

      pitch_accOff += (atan((yAcc) / sqrt(pow((xAcc), 2) + pow((zAcc), 2))) * RAD_TO_DEG);
      roll_accOffset += (atan(-1 * (xAcc) / sqrt(pow((yAcc), 2) + pow((zAcc, 2))) * RAD_TO_DEG);

      if(i == 199)
      {
        roll_accOff = roll_accOffset / 200;
        pitch_accOff = pitch_accOffset / 200;
      }
    }
  }

  if(r)

}
