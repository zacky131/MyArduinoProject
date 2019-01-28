#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
 
/* Set these to your desired credentials. */
const char *ssid = "La Maison";  //ENTER YOUR WIFI SETTINGS <<<<<<<<<
const char *password = "12345678";
 
//Web address to read from
const char *host = "https://api.thingspeak.com/update?api_key=LB59XK4AUN1O15OJ&field1=0";
String apiKey = "LB59XK4AUN1O15OJ";  //ENTER YOUR API KEY <<<<<<<<<<<

//=======================================================================
//                    Power on setup
//=======================================================================

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
 
void setup() {
  delay(1000);
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  //WiFi.mode(WIFI_AP_STA);   //Both hotspot and client are enabled
  //WiFi.mode(WIFI_AP);       //Only Access point
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}





// defines variables
long duration;
int distance;


void loop() {
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
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
Serial.println(distance);
delay(1000);
}
