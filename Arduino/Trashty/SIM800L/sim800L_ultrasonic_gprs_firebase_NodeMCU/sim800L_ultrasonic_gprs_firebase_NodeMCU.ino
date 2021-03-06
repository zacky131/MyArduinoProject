#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>

#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <Ultrasonic.h>

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> 


#include <time.h>


//Firebase definition
#define FIREBASE_HOST "home-automation-17d36.firebaseio.com"  //Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "miLalomNlIYgjlYjDXgJOVV98fBCbsbnsatAEe2k" //Firebase Database Secret




// defines pins numbers ultrasonic
Ultrasonic ultrasonic(5, 4);   //(trigger, echo)

// defines variables
int distance;
int distance_percent;
int trashbin_size = 100; // in cm
int timezone = 7; //(GMT)
int dst = 0;


//define sofware serial
SoftwareSerial MySerial(14,12); // D5, D6 // TX, RX

void setup() {
  //serial setup IDE to nodemcu
  Serial.begin(9600);

  //Serial communication Nodemcu to sim800L
  MySerial.begin(9600)
  Serial.println("Initializing..."); 
  delay(1000);
  
  //setup SIM800L
  Serial.println("Setup GPRS - HTTP Connection");
  
  MySerial.println("AT+CFUN=1"); //default was  Serial.println("AT Command")
  delay(1000);
  
  MySerial.println("AT+CPIN?");
  updateSerial();
  delay(1000);

  MySerial.println("AT+CSTT=\"m2mdev\",\"\",\"\"");  // setup APN password
  updateSerial();
  delay(1000);

  MySerial.println("AT+CIFSR");
  updateSerial();
  delay(1000);
  
 
  //Setup timestamp
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(""); 

  //Connect to firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  // Define initial variable in Firebase database
  // Harus di ubah tiap device akan beda
  Firebase.setString("locations/6/SerialNumber","Trsh0006");
  Firebase.setString("locations/6/Address","Pemkot depok");
  Firebase.setFloat("locations/6/Latitude", -6.397910); 
  Firebase.setFloat("locations/6/Longitude", 106.822080); 

}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //time setup
  time_t now = time(nullptr);
  Serial.println(ctime(&now));
  delay(1000);    

   //firebase setup
   if (Firebase.failed()){
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
   }
   
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

  Firebase.setString("locations/6/Time",ctime(&now));
  Firebase.setInt("locations/6/RawFillLevel",distance_percent);
  Firebase.setInt("locations/6/RawTrashDistance",distance);

  // Push data to serial and Firebase
 if (distance >= 0 && distance <= 100){
     Firebase.setInt("locations/6/FillLevel",distance_percent);
   
 }
  
 if (distance_percent >= 0 && distance_percent <= 100){
     Firebase.setInt("locations/6/TrashDistance",distance); 
      
  }
   delay(5000);
   
Serial.println("Going into deep sleep");
ESP.deepSleep(10e6); // 10 seconds
    
}

void updateSerial(){
  delay(500);
  while (Serial.available()){
    MySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(MySerial.available()){
    Serial.write(MySerial.read());//Forward what Software Serial received to Serial Port
  }
}
