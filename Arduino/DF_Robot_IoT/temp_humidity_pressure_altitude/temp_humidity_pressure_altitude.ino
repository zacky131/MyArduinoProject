#include <DFRobot_BME280.h>

#define SEA_LEVEL_PRESSURE  1013.25f
#define BME_CS 10

DFRobot_BME280 bme; //I2C

float temp, pa, hum, alt;

void setup() {
    Serial.begin(115200);
    
    // I2c default address is 0x76, if the need to change please modify bme.begin(Addr)
    if (!bme.begin()) {
        Serial.println("No sensor device found, check line or address!");
        while (1);
    }
    
    Serial.println("-- BME280 DEMO --");
}

void loop() { 
  temp = bme.temperatureValue();
  pa = bme.pressureValue();
  hum = bme.humidityValue();
  alt = bme.altitudeValue(SEA_LEVEL_PRESSURE);
  
  Serial.print("Temp:");
  Serial.print(temp);
  Serial.println(" C");
  
  Serial.print("Pa:");
  Serial.print(pa);
  Serial.println(" Pa");
  
  Serial.print("Hum:");
  Serial.print(hum);
  Serial.println(" %");
  
  Serial.print("Alt:");
  Serial.print(alt);
  Serial.println(" m");
  
  Serial.println("------END------");
  
  delay(1000);
}
