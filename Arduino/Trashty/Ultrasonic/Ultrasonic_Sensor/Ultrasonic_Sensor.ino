#include <Ultrasonic.h>
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  



// defines pins numbers ultrasonic
Ultrasonic ultrasonic(5, 4);   //D1, D2 (trigger, echo)

// defines variables
int distance;
int distance_percent;
int trashbin_size = 100; // in cm






void setup(){  
  Serial.begin(115200);  
  delay(10);
  
}

void loop(){  
 
  //read measurement
  distance = ultrasonic.read();
  
  // Calculating the distance percentage
  distance_percent = 100 - distance*100/trashbin_size;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("Fill level: ");
  Serial.print(distance_percent);
  Serial.println("%");
  delay(2000);


}
