const int hydrogenLED = 12;
#include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");
  dht.begin();
  pinMode(hydrogenLED,OUTPUT);
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print("\n");
if(t < 40)
  {
 digitalWrite(hydrogenLED, HIGH);
}
else{
 digitalWrite(hydrogenLED, LOW);
  
}
  delay(1000);
}
