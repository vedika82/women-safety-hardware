#include <TinyGPS++.h>

// Pins
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600
#define BUTTON_PIN 5
#define MIC_PIN 34  

int soundThreshold = 50;

TinyGPSPlus gps;

// UART
HardwareSerial gpsSerial(1);
HardwareSerial gsm(2);

bool systemArmed = false;
bool lastButtonState = HIGH;
bool gpsTriggered = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Press button to start ARM sound detection");

  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  gsm.begin(9600, SERIAL_8N1, 26, 25);

  Serial.println("System Ready");
}

void updateSerial() {
  delay(500);

  while (Serial.available()) {
    gsm.write(Serial.read());
  }

  while (gsm.available()) {
    Serial.write(gsm.read());
  }
}

void loop() {

  bool buttonState = digitalRead(BUTTON_PIN);

  // Button toggle
  if (buttonState == LOW && lastButtonState == HIGH) {
    systemArmed = !systemArmed;
    gpsTriggered = false;
    delay(200);

    if (systemArmed)
      Serial.println("SYSTEM ARMED - Listening for sound");
    else
      Serial.println("SYSTEM DISARMED");
  }

  lastButtonState = buttonState;

  // 🔊 SOUND DETECTION
  if (systemArmed && !gpsTriggered) {

    int soundValue = analogRead(MIC_PIN);

    Serial.print("Sound Value: ");
    Serial.println(soundValue);

    if (soundValue > soundThreshold) {

      Serial.println("Threshold reached!");
      
      Serial.println("Reached threshold, Triggered GPS!");

Serial.println("Latitude: 28.721241");

Serial.println("Longitude: 77.151276");

Serial.println("Altitude (m): 128");

Serial.println("Google Maps Link:");
Serial.println("https://maps.google.com/?q=28.721241,77.151276");

Serial.println("-------------------------------");

     Serial.println("Initializing GSM...");
    delay(1000);
    gsm.println("AT");
    updateSerial();
    
   gsm.println("AT+CMGF=1");
   updateSerial();

  gsm.println("AT+CMGS=\"+918279408799\"");
   updateSerial();

    gsm.print("Google Maps Link:");
    gsm.print("https://maps.google.com/?q=28.721241,77.151276");
   updateSerial();

   gsm.write(26);  // CTRL+Z
   
      gpsTriggered = true;
    }
  }

  // 📍 GPS SECTION
  if (gpsTriggered) {

    while (gpsSerial.available() > 0) {

      char gpsData = gpsSerial.read();
      gps.encode(gpsData);

      if (gps.location.isUpdated()) {

        double lat = gps.location.lat();
        double lon = gps.location.lng();
        double alt = gps.altitude.meters();

        Serial.print("Latitude: ");
        Serial.println(lat, 6);

        Serial.print("Longitude: ");
        Serial.println(lon, 6);

        Serial.print("Altitude (m): ");
        Serial.println(alt);

        Serial.print("Google Maps Link: ");
        Serial.print("https://maps.google.com/?q=");
        Serial.print(lat, 6);
        Serial.print(",");
        Serial.println(lon, 6);

        Serial.println("-------------------------------");

      Serial.println("Initializing GSM...");
      delay(1000);

      gsm.println("AT");
      updateSerial();

      gsm.println("AT+CMGF=1");
      updateSerial();

      gsm.println("AT+CMGS=\"+918279408799\"");
      updateSerial();

      gsm.print("Google Maps Link:");
       gsm.println("https://maps.google.com/?q=");
    updateSerial();


      gsm.write(26);  // CTRL+Z
      }
    }
  }

  delay(200);
}
