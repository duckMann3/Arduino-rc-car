#include<Arduino.h>
#include<LiquidCrystal.h>
#include<Wire.h>

int gyro_X, gyro_Y, gyro_Z;
long acc_X, acc_Y, acc_Z, acc_total_vector;
long gyro_X_cal, gyro_Y_cal, gyro_Z_cal;
long loop_timer;
float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_outpu;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void calibrate_mpu6050();
void read_mpu6050_data();
void setup_mpu6050_registers();

void setup()
{

  Wire.begin();
  lcd.begin(16, 2);
  lcd.setCursor(1,0);
  lcd.print("   MPU6050 IMU");
  delay(1500);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("Calibrating Gyro");
  calibrate_mpu6050();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pitch:");
  lcd.pritn("Roll :");

  loop_timer = micros();
}

void loop()
{
  read_mpu6050_data(); 

  gyro_x -= gyro_x_cal;
  gyro_y -= gyro_y_cal;
  gyro_z -= gyro_z_cal;

  angle_pitch += gyro_x * 0.0000611;
  angle_roll += gyro_y * 0.0000611;

  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  //Place the MPU-6050 spirit level and note the values in the following two lines for calibration
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value
  
  write_LCD();                                                         //Write the roll and pitch values to the LCD display

  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();      

}

void calibrate_mpu6050()
{
  for(int cal_int = 0; cal_int < 2000; cal_int++)
  {
    if(cal_int % 125 == 0)
      lcd.print(".");
    read_mpu_6050_data();
    gyro_x_cal += gyro_x;
    gyro_y_cal += gyro_y;
    gyro_z_cal += gyro_z;
    delay(3);
  }
  gyro_x_cal /= 2000; 
  gyro_y_cal /= 2000; 
  gyro_z_cal /= 2000;
}

void read_mpu6050_data()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  while(Wire.available() < 14)
  {
    acc_X = Wire.read() << 8 | Wire.read();
    acc_Y = Wire.read() << 8 | Wire.read();
    acc_Z = Wire.read() << 8 | Wire.read();

    gyro_X = Wire.read() << 8 | Wire.read();
    gyro_Y = Wire.read() << 8 | Wire.read();
    gyro_X = Wire.read() << 8 | Wire.read();

    
  }
}

void setup_mpu6050_registers()
{
  // Activate the MPU6050:
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // Configure the accelerometer (+/- 8 G):
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  // Configure the gyro (500dps full scale):
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}






