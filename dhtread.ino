#include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("BEGIN!");
  dht.begin();
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
}
