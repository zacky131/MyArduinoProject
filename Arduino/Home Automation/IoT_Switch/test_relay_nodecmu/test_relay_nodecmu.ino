int relay1 = 5; // D1
int relay2 = 4; // D2
int relay3 = 14; // D5
int relay4 = 12; // D6

void setup() {

  pinMode(relay1, OUTPUT); // initialize pin as OUTPUT
  pinMode(relay2, OUTPUT); // initialize pin as OUTPUT
  pinMode(relay3, OUTPUT); // initialize pin as OUTPUT
  pinMode(relay4, OUTPUT); // initialize pin as OUTPUT

  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW);
  digitalWrite(relay4,LOW);

}
void loop() {
  digitalWrite(relay1, HIGH); // turn relay on

  delay(500);

  digitalWrite(relay2, HIGH); // turn relay on

  delay(500);
  
  digitalWrite(relay3, HIGH); // turn relay on

  delay(500);

  digitalWrite(relay4, HIGH); // turn relay on

  delay(500);
  
  digitalWrite(relay1, LOW); // turn relay off

  delay(500);


  digitalWrite(relay2, LOW); // turn relay off

  delay(500);



  digitalWrite(relay3, LOW); // turn relay off

  delay(500);



  digitalWrite(relay4, LOW); // turn relay off

  delay(500);
}
