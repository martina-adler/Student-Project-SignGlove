const int thumb = 13; // Pin for Flex-Sensor on Thumb
const int indexfinger = 12; // Pin for Flex-Sensor on index finger
const int middle = 14; // Pin for Flex-Sensor on middle finger
const int ring = 27; // Pin for Flex-Sensor on ring finger
const int pinkie = 26; // Pin for Flex-Sensor on pinkie finger
const int wrist = 25; // Pin for Flex-Sensor over wrist

void setup() {
  Serial.begin(115200); // Start seriellcommunikation with 115200 Baud
}

void loop() {
  // read out raw data of flex sensors
  int Value_thumb = analogRead(thumb);
  int Value_indexfinger = analogRead(indexfinger);
  int Value_middle = analogRead(middle);
  int Value_ring = analogRead(ring);
  int Value_pinkie = analogRead(pinkie);
  int Value_wrist = analogRead(wrist);

  // print values of flex sensors in seriel monitor
  Serial.print("Thumb: ");
  Serial.print(Value_thumb);
  Serial.print("Index finger: ");
  Serial.print(Value_indexfinger);
  Serial.print("Middle finger: ");
  Serial.print(Value_middle);
  Serial.print("Ring finger: ");
  Serial.print(Value_ring);
  Serial.print("Pinkie finger: ");
  Serial.println(Value_pinkie);
  Serial.print("Wrist: ");
  Serial.println(Value_wrist);
  

  delay(250); // delay for stability and gathering data in serial plot
}
