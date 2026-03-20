#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(2000);

  // Test communication
  mySerial.println("AT");
  delay(1000);
  showResponse();

  // Set SMS text mode
  mySerial.println("AT+CMGF=1");
  delay(1000);
  showResponse();

  // Send SMS
  mySerial.println("AT+CMGS=\"+918279408799\"");
  delay(1000); // wait for '>'

  mySerial.print("Hello from Vedika GSM 🚀");
  delay(500);

  mySerial.write(26); // CTRL+Z to send
  delay(5000); // wait for sending

  showResponse();
}

void loop()
{
}

// Function to print SIM800L response
void showResponse()
{
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}
