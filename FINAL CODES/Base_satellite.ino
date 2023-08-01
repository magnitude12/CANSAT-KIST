//this is the base code for TAN CANSAT, all 3 teams include these 3 sensors and will add a unique sensor of their own.
//unique sensors : TEAM JAMES- UV SENSOR, TEAM HYDROGEN- HCSR04, TEAM PAISA- MQ4 GAS Sensor
//teams will send a pr with each of their unique codes
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define DHTPIN 3
#define DHTTYPE DHT11
#define seaLevelPressure_hPa 1013.25


BH1750 lightMeter;
Adafruit_MPU6050 mpu;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

RF24 radio(9, 10);
const byte address[6] = "00001";

struct SensorData {
  float lux;
  float humid;
  float tempr;
  float pressure;
  float altitude;
  float accelX;
  float accelY;
  float accelZ;
  float gyroX;
  float gyroY;
  float gyroZ;
};

SensorData sensorData;

void setup(void) {
  Serial.begin(115200);
  Serial.println("startup MPU6050!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  lightMeter.begin();
  Serial.println(F("BH1750 Start"));
  dht.begin();
  
   if (!bmp.begin()) {
  Serial.println("BMP180 Not Found. CHECK CIRCUIT!");
  while (1) {}
  }


}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  sensorData.lux = lightMeter.readLightLevel();
  sensorData.humid = dht.readHumidity();
  sensorData.tempr = dht.readTemperature();
  sensorData.pressure = bmp.readPressure();
  sensorData.altitude = bmp.readAltitude(seaLevelPressure_hPa);
  sensorData.accelX = a.acceleration.x;
  sensorData.accelY = a.acceleration.y;
  sensorData.accelZ = a.acceleration.z;
  sensorData.gyroX = g.gyro.x;
  sensorData.gyroY = g.gyro.y;
  sensorData.gyroZ = g.gyro.z;

  // Transmit sensor data via nRF24L01
  radio.write(&sensorData, sizeof(sensorData));

  delay(500);
}