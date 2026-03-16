// Define the RX and TX pins for Serial 2
#include <TinyGPS++.h>

// Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600
#define BUTTON_PIN 5
#define MIC_PIN 34

int soundThreshold = 50;
TinyGPSPlus gps;

// Create an instance of the HardwareSerial class for Serial 2
HardwareSerial gpsSerial(2);

bool systemArmed = false;
bool lastButtonState = HIGH;

void setup(){
  // Serial Monitor
  Serial.begin(115200);
   pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Press button to start ARM sound detection");
  
  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 started at 9600 baud rate");
}

void loop(){
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect button press
  if(buttonState == LOW && lastButtonState == HIGH){
    systemArmed = !systemArmed;
    delay(200);

     if(systemArmed)
      Serial.println("SYSTEM ARMED - Listening for sound");
    else
      Serial.println("SYSTEM DISARMED");
      
//    if(gpsRunning)
//      Serial.println("GPS STARTED");
//    else
//      Serial.println("GPS STOPPED");

  }

  lastButtonState = buttonState;

if(systemArmed){
  
 int soundValue = analogRead(MIC_PIN);

    Serial.print("Sound Value: ");
    Serial.println(soundValue);

    // Trigger GPS when loud sound detected
    if(soundValue > soundThreshold){
      Serial.println("Sound Triggered GPS!");
      
  // Run GPS only when enabled
  while (gpsSerial.available() > 0){
    // get the byte data from the GPS
    char gpsData = gpsSerial.read();
     gps.encode(gpsData);

    if (gps.location.isUpdated()){

      double lat = gps.location.lat();
      double lon = gps.location.lng();
      double alt = gps.altitude.meters();

      Serial.print("Latitude: ");
      Serial.println(lat,6);

      Serial.print("Longitude: ");
      Serial.println(lon,6);

      Serial.print("Altitude (m): ");
      Serial.println(alt);

      Serial.print("Google Maps Link: ");
      Serial.print("https://maps.google.com/?q=");
      Serial.print(lat,6);
      Serial.print(",");
      Serial.println(lon,6);

      Serial.println("-------------------------------");
    //Serial.print(gpsData);
  }
}}}
delay (200);} 
