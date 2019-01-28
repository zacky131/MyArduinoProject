#include <DHT.h>  
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <SoftwareSerial.h>
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  

// defines pins numbers ultrasonic
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
const char* dweet_line = "/dweet/for/trashty131";
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// defines variables
long duration;
int distance;
int distance_percent;
const char* ssid = "AzUz";  
const char* password = "muhamm4d";  

// Host
const char* host = "dweet.io";

WiFiClient client;  
uint8_t temperature, humidity;  



void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  ss.begin(GPSBaud);
  
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  
  //define pin ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);  
  delay(10);  
}  
void loop() {  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
    // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  
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
  distance_percent = 100 - distance*100/16;
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("Fill level: ");
  Serial.print(distance_percent);
  Serial.println("%");
  Serial.print("Latitude= "); 
  Serial.print(gps.location.lat(), 6);
  Serial.print(" Longitude= "); 
  Serial.println(gps.location.lng(), 6);

  Serial.print("Connecting to ");
  Serial.println(host);
  
  // This will send the request to the server
  client.print(String("GET /dweet/for/trashty131?trashlevel=") + String(distance) + "&temperature=" + String(temperature) 
              + "&humidity=" + String(humidity)+ "&fill_level=" + String(distance_percent)+ 
              + "&Latitude= " + String(gps.location.lat()) + "&Longitude= " + String(gps.location.lng()) +  " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);   }
    
  Serial.println();
  Serial.println("closing connection");
  
  // Repeat every 2 seconds
  delay(2000);
} 
