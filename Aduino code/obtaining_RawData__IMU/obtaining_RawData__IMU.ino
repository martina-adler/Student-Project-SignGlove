#include<Wire.h>
const int MPU_ADDR = 0x68;    // MPU6050 (IMU) Address for  I2c communication  
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;   // Acceleration, temperature and angular velocity for each axis 
void readRawData();  // function to obtain IMU data

void setup() {
  initSensor();
  Serial.begin(115200);
  delay(300);        
}


void loop() {
 readRawData();          // call the function 

  Serial.print("AcX:");
  Serial.print(AcX);
  Serial.print(" ");  // for serial plotter 
  Serial.print(" AcY :");
  Serial.print(AcY);
  Serial.print(" ");  // for serial plotter 
  Serial.print(" AcZ :");
  Serial.print(AcZ);
  Serial.print(" ");  // for serial plotter 
  Serial.print("GyX:");
  Serial.print(GyX);
  Serial.print(" ");  // for serial plotter 
  Serial.print(" GyY :");
  Serial.print(GyY);
  Serial.print(" ");  // for serial plotter 
  Serial.print(" GyZ :");
  Serial.print(GyZ);
  Serial.println();
  delay(250);  // delay for stability and gathering data in serial plot
}

void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);   // I2C address
  Wire.write(0x6B);    // Power Management Register 107, starting communication, slave address (default:0x68) 
  Wire.write(0);       // wakes up the MPU-6050 
  Wire.endTransmission(true);
}

void readRawData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);   // AcX address 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  // 14 Byte after AcX address 

  AcX = Wire.read() << 8 | Wire.read(); //Merging 2 Bytes by OR operator and the shift operators
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}
