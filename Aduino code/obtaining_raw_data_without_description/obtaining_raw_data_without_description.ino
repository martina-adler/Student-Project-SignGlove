#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
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

Adafruit_MPU6050 mpu;
long last_sample_millis = 0;
char a;
bool capture = false;

void setup() {
  initSensor();
  Serial.begin(115200); //start serial communication with 115200 baud
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console open      
}
  // Try to initialize!
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(10);
    //while (1) {
      //delay(10);
    //}
  }
   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  // insert flex sensor raw data reading as well here
  Serial.println("");
  delay(100);
}


void loop() {
  //start and stop recording
   if (Serial.available() > 0) {
    a = Serial.read();
    if (a == 'o') {
      Serial.print("-,-,-\n");
      capture = true;
    } else if (a == 'p') {
      capture = false;
      Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n"); //adapt amount of ns to include number of flex sensors +5 mal \n
    }
  }
  if (capture) {
    capture_data();
  }
}
  
void capture_data() {
  /* Get new sensor events with the readings */
  if ((millis() - last_sample_millis) >= 40) {
    
    last_sample_millis = millis();
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // include here flex sensor read out         // call the function to read raw data IMU
 
    // read out raw data of flex sensors
  int Value_thumb = analogRead(thumb);
  int Value_indexfinger = analogRead(indexfinger);
  int Value_middle = analogRead(middle);
  int Value_ring = analogRead(ring);
  int Value_pinkie = analogRead(pinkie);
  int Value_wrist = analogRead(wrist);

  //IMU 
  Serial.print(AcX);
   Serial.print(",");
  Serial.print(AcY);
   Serial.print(",");
  Serial.print(AcZ);
   Serial.print(",");
  Serial.print(GyX);
   Serial.print(",");
  Serial.print(GyY);
   Serial.print(",");
  Serial.print(GyZ);
   Serial.print(",");


  // print values of flex sensors in seriel monitor
  Serial.print(Value_thumb);
   Serial.print(",");
  Serial.print(Value_indexfinger);
    Serial.print(",");
  Serial.print(Value_middle);
   Serial.print(",");
  Serial.print(Value_ring);
   Serial.print(",");
  Serial.print(Value_pinkie);
   Serial.print(",");
  Serial.println(Value_wrist);
 
  delay(250); // delay for stability and gathering data in serial plot
}
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
