
#include <DHT.h>  
#include <ESP8266WiFi.h>  
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  



 
// defines variables
uint8_t temperature, humidity; 



// Host
const char* ssid = "LaMaison";  
const char* password = "12345678"; 

void setup()  
{  
  Serial.begin(115200);  
  delay(10);  
  dht.begin();

  
}  
void loop() {  

  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();  
  delay(1000);

  //serial print
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%"); 

  }
