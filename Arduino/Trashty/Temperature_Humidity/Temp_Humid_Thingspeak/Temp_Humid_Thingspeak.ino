#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#define DHTPIN1 D5  
#define DHTPIN2 D8  
#define DHTPIN3 D0 
#define DHTTYPE DHT11  


DHT dht1(DHTPIN1, DHTTYPE);  
DHT dht2(DHTPIN2, DHTTYPE); 
DHT dht3(DHTPIN3, DHTTYPE); 

const char* ssid = "LaMaison";  
const char* password = "12345678";  
WiFiClient client;  
unsigned long myChannelNumber = 628861;  
const char * myWriteAPIKey = "LB59XK4AUN1O15OJ";  
uint8_t temp1, hum1; 
uint8_t temp2, hum2; 
uint8_t temp3, hum3; 
 
void setup()  
{  
  Serial.begin(115200);  
  dht1.begin();  
  dht2.begin(); 
  dht3.begin();   
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
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
  temp3 = dht3.readTemperature();  
  hum3 = dht3.readHumidity(); 
  delay(1000); 
  
  Serial.print("Temperature 1 :");  
  Serial.print(temp1);  
  Serial.println("C");  
  ThingSpeak.writeField(myChannelNumber, 1, temp1, myWriteAPIKey); // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different pieces of information in a channel. 
  delay(65000);
  
  Serial.print("Humidity 1 :");  
  Serial.print(hum1);  
  Serial.println("%");  
  ThingSpeak.writeField(myChannelNumber, 2, hum1, myWriteAPIKey);  
  delay(65000); // ThingSpeak will only accept updates every 15 seconds.  

  Serial.print("Temperature 2 :");  
  Serial.print(temp2);  
  Serial.println("C");  
  ThingSpeak.writeField(myChannelNumber, 3, temp2, myWriteAPIKey); // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different pieces of information in a channel. 
  delay(65000);
  
  Serial.print("Humidity 2 :");  
  Serial.print(hum2);  
  Serial.println("%");  
  ThingSpeak.writeField(myChannelNumber, 4, hum2, myWriteAPIKey);  
  delay(65000); // ThingSpeak will only accept updates every 15 seconds.  

  Serial.print("Temperature 3 :");  
  Serial.print(temp3);  
  Serial.println("C");  
  ThingSpeak.writeField(myChannelNumber, 5, temp3, myWriteAPIKey); // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different pieces of information in a channel. 
  delay(65000);
  
  Serial.print("Humidity 3 :");  
  Serial.print(hum3);  
  Serial.println("%");  
  ThingSpeak.writeField(myChannelNumber, 6, hum3, myWriteAPIKey);  
  delay(65000); // ThingSpeak will only accept updates every 15 seconds.  


  
}
