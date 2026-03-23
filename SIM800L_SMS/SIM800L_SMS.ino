HardwareSerial gsm(2);  // Use UART2

void setup()
{
  Serial.begin(115200);

  // RX = 25, TX = 26 (change if needed)
  gsm.begin(9600, SERIAL_8N1, 26, 25);

  Serial.println("Initializing...");
  delay(1000);

  gsm.println("AT");
  updateSerial();

  gsm.println("AT+CMGF=1");
  updateSerial();

  gsm.println("AT+CMGS=\"+918279408799\"");
  updateSerial();

  gsm.print("hello the person needs your help :link of location");
  updateSerial();
 
  gsm.write(26);  // CTRL+Z to send SMS
}

void loop()
{
}

void updateSerial()
{
  delay(500);

  while (Serial.available())
  {
    gsm.write(Serial.read());
  }

  while (gsm.available())
  {
    Serial.write(gsm.read());
  }
}
