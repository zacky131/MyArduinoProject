#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#define DHTPIN1 D5  
#define DHTPIN2 D8  
#define DHTTYPE DHT11  


DHT dht1(DHTPIN1, DHTTYPE);  
DHT dht2(DHTPIN2, DHTTYPE);  

const char* ssid = "LaMaison";  
const char* password = "12345678";  
WiFiClient client;  
unsigned long myChannelNumber = 628861;  
const char * myWriteAPIKey = "LB59XK4AUN1O15OJ";  
uint8_t temp1, hum1; 
uint8_t temp2, hum2; 
 
void setup()  
{  
  Serial.begin(115200);  
  dht1.begin();  
  dht2.begin(); 
}  
void loop()   
{  
  static boolean data_state = false;  
  temp1 = dht1.readTemperature();  
  hum1 = dht1.readHumidity();  
  delay(1000);
  temp2 = dht2.readTemperature();  
  hum2 = dht2.readHumidity(); 
  delay(1000); 
  
  Serial.print("Temperature 1 :");  
  Serial.print(temp1);  
  Serial.println("C");  
   
  delay(1000);
  Serial.print("Humidity 1 :");  
  Serial.print(hum1);  
  Serial.println("%");  

  delay(1000); // ThingSpeak will only accept updates every 15 seconds.  

  Serial.print("Temperature 2 :");  
  Serial.print(temp2);  
  Serial.println("C");  
  
  delay(1000);
  Serial.print("Humidity 2 :");  
  Serial.print(hum2);  
  Serial.println("%");  
  delay(1000); // ThingSpeak will only accept updates every 15 seconds.  
}
