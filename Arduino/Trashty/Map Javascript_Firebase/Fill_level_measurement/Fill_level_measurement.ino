#include <Esplora.h>

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
int trashbin_size = 100; // in cm
int timezone = 7 * 3600;
int dst = 0;

//Wifi setting
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

  //Time stamp
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 

  //Connect to firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

  // Define initial variable in Firebase database
  Firebase.setString("tempat/0/SerialNumber","Trsh0000");
  Firebase.setFloat("tempat/0/Latitude", -6.245760); 
  Firebase.setFloat("tempat/0/Longitude",106.940559); 
  
}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){  
  //time setup
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  
  Serial.print(" ");
  
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.println(p_tm->tm_sec);
//  Firebase.setInt("tempat/0/Time", p_tm->tm_mday + "/" + p_tm->tm_mon + 1 + "/" + p_tm->tm_year + 1900
//  + "/" + p_tm->tm_hour + ":" + p_tm->tm_min + ":" + p_tm->tm_sec);

  
  
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

  // Push data to serial and Firebase
  if (distance >= 0 && distance <= 100){
      Firebase.setInt("tempat/0/FillLevel",distance_percent);
      Firebase.pushInt("tempat/0/Fill",distance_percent);
      
  }
  
  if (distance_percent >= 0 && distance_percent <= 100){
      Firebase.setInt("tempat/0/TrashDistance",distance); 
      Firebase.pushInt("tempat/0/Distance",distance);         
   }


  Serial.println("Going into deep sleep for 10 seconds");
  ESP.deepSleep(10e6); // 10 seconds
} 
