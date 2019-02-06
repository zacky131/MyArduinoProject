#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);

    Serial.println("Turning ON SIM7000......");
    if(sim7000.turnON()){                             //Turn ON SIM7000
        Serial.println("Turned ON !");
    }

    Serial.println("Set baud rate......");
    if(sim7000.setBaudRate(19200)){                   //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
    }else{
        Serial.println("Failed to set baud rate");
        while(1);
    }

    mySerial.begin(19200);
    Serial.println("For example, if you type AT\\r\\n, OK\\r\\n will be responsed!");
    Serial.println("Enter your AT command :");
}

void loop() {
    mySerial.listen();
    while(mySerial.available()){
        Serial.write(mySerial.read());
    }

    mySerial.flush();
    while(Serial.available()){
        mySerial.write(Serial.read());
    }

    delay(100);
    
}
