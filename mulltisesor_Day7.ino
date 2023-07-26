
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const int trigPin = 12;
const int echoPin = 13 ;
#define DHTPIN 2  
#define SOUND_SPEED 0.033
#define DHTTYPE DHT11
#define seaLevelPressure_hPa 1013.25

BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);
long duration;
float distanceCm;
Adafruit_BMP085 bmp;

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

  if (!mpu.begin()) {
  Serial.println("Sensor init failed");
  while (1)
}
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.setGyroRange(MPU6050_RANGE_500_DEG);

Serial.begin(115200);
  if (!bmp.begin()) {
  Serial.println("BMP180 Not Found. CHECK CIRCUIT!");
  while (1) {}
  }
}
void loop() {

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Ultrasonic
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  //DHT
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print("\n");

  //light sensor
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  //Accelerometer
  Serial.print(a"Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  //Gyroscope
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

 //Pressure
 Serial.print("Pressure = ");
 Serial.print(bmp.readPressure());
 Serial.println(" Pa");

//Crash sensor
int val = digitalRead(inputPin);  
  if (val == HIGH) {                
    digitalWrite(ledPin, LOW);      
  } else {
    digitalWrite(ledPin, HIGH);     
    Serial.println("Switch Pressed!");
  }
  delay(500);
}
