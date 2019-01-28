#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  

// defines pins numbers ultrasonic
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// defines variables
long duration;
int distance;
const char* ssid = "Nokia_6";  
const char* password = "muhamm4d";  
WiFiClient client;  
unsigned long myChannelNumber = 628861;  
const char * myWriteAPIKey = "LB59XK4AUN1O15OJ";  
uint8_t temperature; 

void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
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
  
  //define pin ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);  
  delay(10);  
}  
void loop()   
{  
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");    
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1.  

  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);    
  ThingSpeak.writeField(myChannelNumber, 3, distance, myWriteAPIKey); 
  delay(1000); // ThingSpeak will only accept updates every 15 seconds.    
} 
