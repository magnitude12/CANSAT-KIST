const int trigPin = 5;
const int echoPin = 4;
#include "DHT.h"

#define DHTPIN 2  
#define SOUND_SPEED 0.033
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
long duration;
float distanceCm;
void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");
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

  delay(500);
}
