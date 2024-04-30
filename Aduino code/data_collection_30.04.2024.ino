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

//calibration factors for flex-sensors
const int streched_value = 1000;
const int bent_value = 0;
const int num_flexsensor = 6; // number of flex sensor
int raw_min[num_flexsensor]; // Array for raw_min values of flex-Sensors
int raw_max[num_flexsensor]; // Array for raw_max values of flex-Sensors
const int finger_pins[num_flexsensor] = {thumb, indexfinger, middle, ring, pinkie, wrist}; // Pins for flex-Sensors
bool calibrationStarted = false; 


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
     if (a == 'c') {
      calibrationStarted = true;
      calibrateSensors(); // if c is pressed in serial monitor, call calibration of flex sensors
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


/*// calculate and print calibrated values
  //use calibration factors to clibrate system
  int c_thumb = map(Value_thumb, raw_min[0], raw_max[0], bent_value, streched_value);
  int c_indexfinger = map(Value_indexfinger, raw_min[1], raw_max[1], bent_value, streched_value);
  int c_middle = map(Value_middle, raw_min[2], raw_max[2], bent_value, streched_value);
  int c_ring = map(Value_ring, raw_min[3], raw_max[3], bent_value, streched_value);
  int c_pinkie = map(Value_pinkie, raw_min[4], raw_max[4], bent_value, streched_value);
  int c_wrist = map(Value_wrist, raw_min[5], raw_max[5], bent_value, streched_value);
  //print mapped/calibrated values of flex sensors
  Serial.print("c_thumb: ");
  Serial.print(c_thumb);
  Serial.print(",");
  Serial.print("c_indexfinger: ");
  Serial.print(c_indexfinger);
  Serial.print(",");
  Serial.print("c_middle: ");
  Serial.print(c_middle);
  Serial.print(",");
  Serial.print("c_ring: ");
  Serial.print(c_ring);
  Serial.print(",");
  Serial.print("c_pinkie: ");
  Serial.print(c_pinkie);
  Serial.print(",");
  Serial.print("c_wrist: ");
  Serial.println(c_wrist);*/
  
  delay(250); // delay for stability and gathering data in serial plot
}
}
void calibrateSensors() {
  Serial.println("Calibration started. please strech your hand");

  // Calibrate raw_max values of each finger
  delay(5000); // pause to strech hand
  for (int i = 0; i < num_flexsensor; i++) {
    int raw_value = analogRead(finger_pins[i]);
    raw_max[i] = raw_value;
  }

  // Calibrate raw_min values of each finger
  Serial.println("please bent each finger after each other.");
  for (int i = 0; i < num_flexsensor; i++) {
    Serial.print("bent ");
    Serial.println(i+1);
    delay(5000); // pause time to bent finger
    int raw_value = analogRead(finger_pins[i]);
    raw_min[i] = raw_value;
  }
  

  //print calibration data for assurance
  Serial.println("Calibration done. Raw values:");
  for (int i = 0; i < num_flexsensor; i++) {
    Serial.print("Finger ");
    Serial.print(i+1);
    Serial.print(": min=");
    Serial.print(raw_min[i]);
    Serial.print(", max=");
    Serial.println(raw_max[i]);
  }
}
