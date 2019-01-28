// Import required libraries
#include "ESP8266WiFi.h"
#include "DHT.h"

// WiFi parameters
const char* ssid = "LaMaison";
const char* password = "12345678";

// Pin
#define DHTPIN D8

// Use DHT11 sensor
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE); 

// Host
const char* host = "dweet.io";

void setup() {
  
  // Start Serial
  Serial.begin(115200);
  delay(10);
  
  // Init DHT 
  dht.begin();

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
 
  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // Reading temperature and humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  delay(1000);


  // Display data
  Serial.print("Temperature :");  
  Serial.print(t);  
  Serial.println("C");  
  Serial.print("Humidity :");  
  Serial.print(h);  
  Serial.println("%"); 
  // This will send the request to the server
  client.print(String("GET /dweet/for/analysetemperature?temperature1=") + String(t) + "&humidity1=" + String(h) + " HTTP/1.1\r\n" +
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
 
}
