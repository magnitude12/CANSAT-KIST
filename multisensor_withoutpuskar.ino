
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>
const int trigPin = 12;
const int echoPin = 13 ;
#define DHTPIN 2  
#define SOUND_SPEED 0.033
#define DHTTYPE DHT11
BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);
long duration;
float distanceCm;
void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Wire.begin();
   lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));


  Serial.begin(115200); 
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print("\n");

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  delay(500);
}
