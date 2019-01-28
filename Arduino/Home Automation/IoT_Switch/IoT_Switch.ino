#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>



#include <ESP8266WiFi.h>
#define FIREBASE_HOST "home-automation-17d36.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "miLalomNlIYgjlYjDXgJOVV98fBCbsbnsatAEe2k"       //Your Firebase Database Secret goes here


#define Relay1 5 //D1
int val1;

#define Relay2 4 //D2
int val2;

#define Relay3 14  //D5
int val3;

#define Relay4 12 //D6
int val4;

const char* WIFI_SSID = "Nokia_6";  //Wifi network name
const char* WIFI_PASSWORD = "muhamm4d"; //Wifi password

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);



  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     //Here the varialbe"S1","S2","S3" and "S4" needs to be the one which is used in our Firebase and MIT App Inventor
  Firebase.setInt("S2",0); 
  Firebase.setInt("S3",0); 
  Firebase.setInt("S4",0); 
 
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  if (Firebase.failed()){
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
   }
      
  val1=Firebase.getString("S1").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val1==1)                                                             // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,LOW);
      Serial.println("light 1 ON");
    }
    else if(val1==0)                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("light 1 OFF");
    }

  val2=Firebase.getString("S2").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val2==1)                                                             // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("light 2 ON");
    }
    else if(val2==0)                                                      // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("light 2 OFF");
    }

   val3=Firebase.getString("S3").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val3==1)                                                             // If, the Status is 1, turn on the Relay3
     {
      digitalWrite(Relay3,LOW);
      Serial.println("light 3 ON");
    }
    else if(val3==0)                                                      // If, the Status is 0, turn Off the Relay3
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("light 3 OFF");
    }

   val4=Firebase.getString("S4").toInt();                                        //Reading the value of the varialble Status from the firebase
  
  if(val4==1)                                                             // If, the Status is 1, turn on the Relay4
     {
      digitalWrite(Relay4,LOW);
      Serial.println("light 4 ON");
    }
    else if(val4==0)                                                      // If, the Status is 0, turn Off the Relay4
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("light 4 OFF");
    }    
}
