
#include <DHT.h>  
#include <ESP8266WiFi.h>  
#define DHTPIN D3  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  


// defines pins numbers ultrasonic
const int trigPin = 12;  //D6
const int echoPin = 13;  //D7

 
// defines variables
uint8_t temperature, humidity; 
long duration;
int distance;
int distance_percent;


// Host
const char* host = "dweet.io";
const char* ssid = "Nokia_6";  
const char* password = "muhamm4d"; 
WiFiClient client;  

void setup()  
{  
  Serial.begin(115200);  
  delay(10);  
  dht.begin();

  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  
  // Print the IP address  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  

  //define pin ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);  
  delay(10);

}  
void loop() {  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  static boolean data_state = false;  
  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();  
  delay(1000);

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

  //serial print
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%"); 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm"); 
  Serial.print("Connecting to ");
  Serial.println(host);

  // This will send the request to the server
    
    client.print(String("GET /dweet/for/trashty") + "?trashlevel=" + String(distance) + "&temperature=" + String(temperature) 
                + "&humidity=" + String(humidity) + "&fill_level=" + String(distance_percent) + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" + 
                "Connection: close\r\n\r\n");
    delay(10);
  
   // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);   }
      
    Serial.println();
    Serial.println("closing connection");
    
    // Repeat every 5 seconds
    delay(2000);

  }
