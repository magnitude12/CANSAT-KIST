#include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int trigPin = 12;
const int echoPin = 13;
#define SOUND_SPEED 0.033

long duration;
float distanceCm;

#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

  
  dht.begin();

   if (!bmp.begin()) {
  Serial.println("BMP180 Not Found. CHECK CIRCUIT!");
  while (1) {}
  }

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print("\n");
  Serial.print(t);
  Serial.print("\n");

  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  /*for BMP180 sensor*/
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    Serial.println(" meters");
    
    Serial.println();
    delay(400);
}
