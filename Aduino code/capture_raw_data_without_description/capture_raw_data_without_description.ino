#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
long last_sample_millis = 0;

//initialize for start/stop function in serial monitor
char a;
bool capture = false;

//initialise flex sensor pins
const int thumb = 13;       // Pin for Flex-Sensor on Thumb             /blue
const int indexfinger = 12; // Pin for Flex-Sensor on index finger      /yellow
const int middle = 14;      // Pin for Flex-Sensor on middle finger     /green
const int ring = 27;        // Pin for Flex-Sensor on ring finger       /orange
const int pinkie = 26;      // Pin for Flex-Sensor on pinkie finger     /violett
const int wrist = 25;       // Pin for Flex-Sensor over wrist           /white


void setup() {
  Serial.begin(115200); //start serial communication with 115200 baud
  while (!Serial) {
    delay(10); // will pause serial monitor until serial console opens      
}
  // Try to initialize!
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}


void loop() {
  //start and stop recording
   if (Serial.available() > 0) {
    a = Serial.read();
    if (a == 'o') {
      Serial.print("\n");
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
 
    // read out raw data of flex sensors
  int Value_thumb = analogRead(thumb);
  int Value_indexfinger = analogRead(indexfinger);
  int Value_middle = analogRead(middle);
  int Value_ring = analogRead(ring);
  int Value_pinkie = analogRead(pinkie);
  int Value_wrist = analogRead(wrist);

  //Print out the values of IMU
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print(a.acceleration.z);
    Serial.print(",");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.print(g.gyro.z);

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
