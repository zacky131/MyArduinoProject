#include <ESP8266WiFi.h>
                               //Password of your wifi network 

int Relay1 = 12; //D6
int Relay2 = 14; //D2
int Relay3 = 4; //D1
int Relay4 = 5; //D5

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Relay1,LOW);
  delay(1000);
  digitalWrite(Relay1,HIGH);
  delay(1000);
  digitalWrite(Relay2,LOW);
  delay(1000);
  digitalWrite(Relay2,HIGH);
  delay(1000);
  digitalWrite(Relay3,LOW);
  delay(1000);
  digitalWrite(Relay3,HIGH);
  delay(1000);
  digitalWrite(Relay4,LOW);
  delay(1000);
  digitalWrite(Relay4,HIGH);
  delay(1000);

}
