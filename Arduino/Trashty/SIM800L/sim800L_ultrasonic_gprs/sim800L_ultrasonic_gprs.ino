#include <Ultrasonic.h>
#include <gprs.h>
#include <SoftwareSerial.h>



// defines pins numbers ultrasonic
Ultrasonic ultrasonic(9, 10);   //(trigger, echo)

// defines variables
int distance;
int distance_percent;
int trashbin_size = 100; // in cm


//define gprs
GPRS gprs;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("GPRS - HTTP Connection");  
  gprs.preInit();
  while(0 != gprs.init()) {
     delay(1000);
     Serial.println("init error");
  }  
  while(!gprs.join("m2mdev")) {  //change "cmnet" to your own APN
      Serial.println("Error joining GPRS network");
      delay(2000);
  }
  // successful DHCP
  Serial.print("IP Address is ");
  Serial.println(gprs.getIPAddress());  
  Serial.println("GPRS Init success");

}

void loop() {    
   
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
