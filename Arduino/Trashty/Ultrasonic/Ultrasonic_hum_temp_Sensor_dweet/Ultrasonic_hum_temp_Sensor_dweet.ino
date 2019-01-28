 // Import required libraries
#include "ESP8266WiFi.h"
#include <DHT.h> 
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE); 

// defines variables
uint8_t temperature, humidity;  
long duration;
int distance;

// WiFi parameters
const char* ssid = "AzUz";
const char* password = "muhamm4d";

// Host
const char* host = "dweet.io";

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3



void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
  dht.begin();  
  delay(10); 

// We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  

 
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
    
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
  distance = duration*0.034/2;

  // Display data
  
  Serial.print("Distance: "); 
  Serial.print(distance);
  Serial.println(" cm ");
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%"); 
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // This will send the request to the server
  client.print(String("GET /dweet/for/trashty131?trashlevel=") + String(distance) + "&humidity=" + String(humidity) + "&temperature=" + String(temperature) +" HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  // Repeat every 5 seconds
  delay(2000);
  
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //delay(1000);
}
