#include<Wire.h>
const int MPU_ADDR = 0x68;    // MPU6050 (IMU) Address for  I2c communication  
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;   // Acceleration, temperature and angular velocity for each axis 
void readRawData();  // function to obtain IMU data

//initialise flex sensor pins
const int thumb = 13;       // Pin for Flex-Sensor on Thumb             /blue
const int indexfinger = 12; // Pin for Flex-Sensor on index finger      /yellow
const int middle = 14;      // Pin for Flex-Sensor on middle finger     /green
const int ring = 27;        // Pin for Flex-Sensor on ring finger       /orange
const int pinkie = 26;      // Pin for Flex-Sensor on pinkie finger     /violett
const int wrist = 25;       // Pin for Flex-Sensor over wrist           /white


void setup() {
  initSensor();
  Serial.begin(115200); //start serial communication with 115200 baud
  delay(300);        
}


void loop() {
 readRawData();          // call the function to read raw data IMU
 
    // read out raw data of flex sensors
  int Value_thumb = analogRead(thumb);
  int Value_indexfinger = analogRead(indexfinger);
  int Value_middle = analogRead(middle);
  int Value_ring = analogRead(ring);
  int Value_pinkie = analogRead(pinkie);
  int Value_wrist = analogRead(wrist);

  Serial.print("AcX:");
  Serial.print(AcX);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print(" AcY :");
  Serial.print(AcY);
  Serial.print(" ");  // for space in serial plotter  
  Serial.print(" AcZ :");
  Serial.print(AcZ);
  Serial.print(" ");  // for space in serial plotter  
  Serial.print("GyX:");
  Serial.print(GyX);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print(" GyY :");
  Serial.print(GyY);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print(" GyZ :");
  Serial.print(GyZ);
  Serial.print(" "); // for space in serial plotter 


  // print values of flex sensors in seriel monitor
  Serial.print("Thumb: ");
  Serial.print(Value_thumb);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print("Index finger: ");
  Serial.print(Value_indexfinger);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print("Middle finger: ");
  Serial.print(Value_middle);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print("Ring finger: ");
  Serial.print(Value_ring);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print("Pinkie finger: ");
  Serial.print(Value_pinkie);
  Serial.print(" ");  // for space in serial plotter 
  Serial.print("Wrist: ");
  Serial.println(Value_wrist);
  

  delay(250); // delay for stability and gathering data in serial plot
}

void initSensor() {
  //initialise IMU
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
