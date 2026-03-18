void setup() {

  Serial.begin(115200);

  delay(2000);  // wait for ESP32-CAM to boot

  Serial.println("START_CAMERA");  // send command
}

void loop() {
  // nothing needed
}
