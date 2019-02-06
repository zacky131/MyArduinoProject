#include <Ultrasonic.h>
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <time.h>

#define FIREBASE_HOST "home-automation-17d36.firebaseio.com"  //Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "miLalomNlIYgjlYjDXgJOVV98fBCbsbnsatAEe2k" //Firebase Database Secret

// defines pins numbers ultrasonic
Ultrasonic ultrasonic(5, 4);   //(trigger, echo)

// defines variables
int distance;
int distance_percent;
int trashbin_size = 100; // in cm, harus di ukur, tiap tempat sampah beda ukuran
int timezone = 7;
int dst = 0;
char num[50] = 

//Wifi setting!!!!!!!!!!!!!!!!!!!!! ini harus di ubah berdasarkan lokasi test
const char* ssid = "LaMaison";  
const char* password = "12345678";  



void setup(){  
  Serial.begin(115200);  
  Serial.println("I'm awake.");
  delay(2000);
  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED){  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  
  // Print the IP address  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  

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
  Firebase.setString("locations/1/SerialNumber","Trsh0001");
  Firebase.setString("locations/1/Address","SMP 8 Bandung");
  Firebase.setFloat("locations/1/Latitude", -6.951580); 
  Firebase.setFloat("locations/1/Longitude", 107.641060); 
  
}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){  
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
  delay(1000);
  
  // Calculating the distance percentage
  distance_percent = 100 - distance*100/trashbin_size;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("Fill level: ");
  Serial.print(distance_percent);
  Serial.println("%");

  Firebase.setString("locations/1/Time",ctime(&now));
  Firebase.setInt("locations/1/RawFillLevel",distance_percent);
  Firebase.setInt("locations/1/RawTrashDistance",distance);

  // Push data to serial and Firebase
 if (distance >= 0 && distance <= 100){
     Firebase.setInt("locations/1/FillLevel",distance_percent);
   
 }
  
 if (distance_percent >= 0 && distance_percent <= 100){
     Firebase.setInt("locations/1/TrashDistance",distance); 
      
  }
   delay(1000);


Serial.println("Going into deep sleep");
ESP.deepSleep(600e6); // 600 seconds
} 
