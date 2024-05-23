#include <Wire.h>
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

/* connect IMU:   
 *  1: VCC to 3V3 (power supply)
 *  2: GND to GND
 *  3: SCL to D22
 *  4: SDA to D21
*/

//calibration factors for flex-sensors
const int streched_value = 1000;
const int bent_value = 0;
const int num_flexsensor = 6; // number of flex sensor
int raw_min[num_flexsensor]; // Array for raw_min values of flex-Sensors
int raw_max[num_flexsensor]; // Array for raw_max values of flex-Sensors
const int finger_pins[num_flexsensor] = {thumb, indexfinger, middle, ring, pinkie, wrist}; // Pins for flex-Sensors
bool calibrationStarted = false;

//initialisation for recording 2 seconds if "s" is pressed
unsigned long recordingStartTime = 0;
const unsigned long recordingDuration = 1500; // recording time in Milliseconds (1 second)
int recordingCount = 0; // Counter for number of recordings
const int maxRecordings = 10; // Maximum number of recordings

void setup() {
  Serial.begin(115200); //start serial communication with 115200 baud
  while (!Serial) {
    delay(10); // will pause serial monitor until serial console opens
  }
  // Try to initialize MPU6050
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
 
    if (a == 's') {
      Serial.print("\n");
      capture = true; // Start recording data
      recordingStartTime = millis(); // start Timer 
      recordingCount = 0; // Reset the counter
      Serial.print("\n\n"); // Insert empty lines for differentiation
    }
    else if (a == 'c') {
      calibrationStarted = true;
      calibrateSensors(); // if c is pressed in serial monitor, call calibration of flex sensors
    }
  }

  if (capture) {
    if (recordingCount < maxRecordings) {
      capture_data();
      
      if (millis() - recordingStartTime >= recordingDuration) { // check if timer expired
        recordingCount++;
        recordingStartTime = millis(); // Reset timer for next recording
        if (recordingCount < maxRecordings) {
          Serial.print("\n\n"); // Insert empty lines for differentiation
        } else {
          capture = false; // Stop recording data after maxRecordings
        }
      }
    }
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

    // Print out the values of IMU
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

    // calculate and print calibrated values
    //use calibration factors to calibrate system
    int c_thumb = map(Value_thumb, raw_min[0], raw_max[0], bent_value, streched_value);
    int c_indexfinger = map(Value_indexfinger, raw_min[1], raw_max[1], bent_value, streched_value);
    int c_middle = map(Value_middle, raw_min[2], raw_max[2], bent_value, streched_value);
    int c_ring = map(Value_ring, raw_min[3], raw_max[3], bent_value, streched_value);
    int c_pinkie = map(Value_pinkie, raw_min[4], raw_max[4], bent_value, streched_value);
    int c_wrist = map(Value_wrist, raw_min[5], raw_max[5], bent_value, streched_value);

    // Print mapped/calibrated values of flex sensors
    Serial.print(c_thumb);
    Serial.print(",");
    Serial.print(c_indexfinger);
    Serial.print(",");
    Serial.print(c_middle);
    Serial.print(",");
    Serial.print(c_ring);
    Serial.print(",");
    Serial.print(c_pinkie);
    Serial.print(",");
    Serial.println(c_wrist);

    delay(10); // delay for stability and gathering data in serial plot
  }
}

void calibrateSensors() {
  Serial.println("Calibration started. Please perform the following movements for calibration:");

  // Stretch hand
  Serial.println("1. Stretch your hand.");
  calibrateMovementMultiple();
  delay(2000); // Pause to stretch hand

  // Ball fist
  Serial.println("2. Ball your fist.");
  calibrateMovementMultiple();
  delay(2000); // Pause to ball fist

  // Bend each finger individually
  // Array with finger names
  const char* finger_names[num_flexsensor] = {"thumb", "index finger", "middle finger", "ring finger", "pinkie Finger", "wrist"};
  Serial.println("3. Bend each finger individually.");
  for (int i = 0; i < num_flexsensor-1; i++) {
    Serial.print("Bend ");
    Serial.print(finger_names[i]); // Namen des aktuellen Fingers ausgeben
    Serial.println();
    calibrateMovementMultiple(i);
    delay(2000); // Pause time to bend finger
  }

  // Move wrist
  Serial.println("4. Move your wrist.");
  calibrateMovementMultiple();
  delay(3000); // Pause to move wrist

  // Print calibration data for assurance
  Serial.println("Calibration done. Raw values:");
  for (int i = 0; i < num_flexsensor; i++) {
    Serial.print(finger_names[i]); // Print the name of the finger
    Serial.print(": min=");
    Serial.print(raw_min[i]);
    Serial.print(", max=");
    Serial.println(raw_max[i]);
  }
}

// Function to calibrate movement and update raw_min and raw_max arrays for all sensors
void calibrateMovementMultiple() {
  int num_measurements = 5; // Number of measurements to take
  for (int m = 0; m < num_measurements; m++) {
    for (int i = 0; i < num_flexsensor; i++) {
      int raw_value = analogRead(finger_pins[i]);
      // Update raw_max if current value is greater
      if (raw_value > raw_max[i]) {
        raw_max[i] = raw_value;
      }
      // Update raw_min if current value is lesser
      if (raw_value < raw_min[i]) {
        raw_min[i] = raw_value;
      }
    }
    delay(100); // Delay between measurements
  }
}

// Function to calibrate movement and update raw_min and raw_max arrays for a specific sensor
void calibrateMovementMultiple(int sensor_index) {
  int num_measurements = 5; // Number of measurements to take
  int max_raw = 0;
  int min_raw = 1023; // Assuming analogRead range is 0-1023
  for (int m = 0; m < num_measurements; m++) {
    int raw_value = analogRead(finger_pins[sensor_index]);
    // Update max_raw if current value is greater
    if (raw_value > max_raw) {
      max_raw = raw_value;
    }
    // Update min_raw if current value is lesser
    if (raw_value < min_raw) {
      min_raw = raw_value;
    }
    delay(100); // Delay between measurements
  }
  // Update raw_max and raw_min arrays for the specific sensor
  // Update raw_max if max_raw is greater
  if (max_raw > raw_max[sensor_index]) {
    raw_max[sensor_index] = max_raw;
  }
  // Update raw_min if min_raw is lesser
  if (min_raw < raw_min[sensor_index]) {
    raw_min[sensor_index] = min_raw;
  }
}
