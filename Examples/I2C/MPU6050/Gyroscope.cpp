#include<Wire.h>
#include<MPU6050.h>

MPU6050 mpu;

void checkSettings();

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!"); 
    delay(500);
  }
  
  mpu.setThreshold(3);
  
}

void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

  Serial.print(" Xraw = ");
  Serial.print(rawGyro.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawGyro.YAxis);
  Serial.print(" Zraw = ");
  Serial.print(rawGyro.Z  Axis);

  Serial.print(" Xnorm = ");
  Serial.print(normGyro.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normGyro.YAxis);
  Serial.print(" Znorm = ");
  Serial.print(normGyro.ZAxis);
  delay(10);
}

void checkSettings()
{
  Serial.println();

  Serial.print(" * Sleep Mode:    ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:      ");
  switch(mpu.getCLockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     
      Serial.println("Stops the clock and keeps the timing generator in reset"); 
      break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: 
      Serial.println("PLL with external 19.2MHz reference"); 
      break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: 
      Serial.println("PLL with external 32.768kHz reference"); 
      break;
    case MPU6050_CLOCK_PLL_ZGYRO:      
      Serial.println("PLL with Z axis gyroscope reference"); 
      break;
    case MPU6050_CLOCK_PLL_YGYRO:      
      Serial.println("PLL with Y axis gyroscope reference"); 
      break;
    case MPU6050_CLOCK_PLL_XGYRO:      
      Serial.println("PLL with X axis gyroscope reference"); 
      break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  
      Serial.println("Internal 8MHz oscillator"); 
      break;
  }

  Serial.print(" * Gyroscope:     ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:
      Serial.println("2000 dps");
      break;
    case MPU6050_SCALE_1000DPS:
      Serial.println("1000 dps");
      break;
    case MPU6050_SCALE_500DPS:
      Serial.println("500 dps");
      break;
    case MPU6050_SCALE_250DPS:
      Serial.println("250 dps");
      break;
  }

  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetZ());

  Serial.println();
}



