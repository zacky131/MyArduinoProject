#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications to computer
  Serial.begin(9600);

  mySerial.begin(9600); // Default for the board
   
  //Clear out any waiting serial data
  while (mySerial.available())
  {
    mySerial.read();
  }  
}

void loop()
{
  /*
   * This loop just takes whatever comes in from the console and sends it to the board
   */
  if (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}
