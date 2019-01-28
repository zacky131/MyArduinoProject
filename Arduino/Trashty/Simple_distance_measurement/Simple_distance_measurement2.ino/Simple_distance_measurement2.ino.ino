// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

const int trigPin2 = 12;
const int echoPin2 = 13;
// defines variables
long duration;
int distance;

long duration2;
int distance2;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
  delay(500);
// Clears the trigPin
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);
// Calculating the distance
distance2= duration2/29/2;
// Prints the distance on the Serial Monitor

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
distance= duration/29/2;
// Prints the distance on the Serial Monitor
Serial.println("{'enter':"+ String(distance) +",'exit':"+ String(distance2) +"}");
}
