#include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int jamesLED=13;

void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");
  dht.begin();
  pinMode(jamesLED,OUTPUT);
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print("\n");
  Serial.print(t);
  Serial.print("\n");
  if (t>30 && h>67){
      digitalWrite(jamesLED,HIGH);
  }
  else{
    digitalWrite(jamesLED,LOW);
  }
}
