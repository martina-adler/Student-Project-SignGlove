const int ledPin =  2;  // Built in  LED = ESP32  :Pin 2  

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay (500);
    digitalWrite(ledPin, LOW);
}
