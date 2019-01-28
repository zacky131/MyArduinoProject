#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// defines variables
long duration;
int distance;

// Set these to run example.
#define FIREBASE_HOST “https://trashty-prototype.firebaseio.com/”
#define FIREBASE_AUTH “”
#define WIFI_SSID “LaMaison”
#define WIFI_PASSWORD “12345678”


void setup() {
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 Serial.begin(9600); // Starts the serial communication
 
// connect to wifi.
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 Serial.print(“connecting”);
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print(“.”);
 delay(500);
 }
 Serial.println();
 Serial.print(“connected: “);
 Serial.println(WiFi.localIP());
 
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.stream("/ultrasonic/NodeCMU")
}

void loop() {
    if (Firebase.failed()) {
      Serial.println("streaming error");
      Serial.println(Firebase.error());
    }

     if (Firebase.available()) {
      // Reads the echoPin, returns the sound wave travel time in microseconds
       duration = pulseIn(echoPin, HIGH);
      
      // Calculating the distance
       distance= duration*0.034/2;

      // Clears the trigPin
       digitalWrite(trigPin, LOW);
       delayMicroseconds(2);
      
      // Sets the trigPin on HIGH state for 10 micro seconds
       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(trigPin, LOW);
       
       FirebaseObject distance = Firebase.readEvent();

      // Prints the distance on the Serial Monitor
       Serial.print("Distance: ");
       Serial.println(distance);
       delay(1000);
      }
}
