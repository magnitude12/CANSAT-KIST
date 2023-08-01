//this is the base receivers for TAN CANSAT, all 3 teams include these 3 sensors and will add a unique sensor of their own.
//unique sensors : TEAM JAMES- UV SENSOR, TEAM HYDROGEN- HCSR04, TEAM PAISA- MQ4 GAS Sensor
//teams will send a pr with each of their unique codes for receivers as well
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
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

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    // Receive sensor data from transmitter
    radio.read(&sensorData, sizeof(sensorData));

    // Display sensor data
    Serial.print("Light: ");
    Serial.print(sensorData.lux);
    Serial.println(" lx");

    Serial.print("Humidity: ");
    Serial.print(sensorData.humid);
    Serial.print(", Temperature: ");
    Serial.print(sensorData.tempr);
    Serial.println(" °C");

    Serial.print("Pressure: ");
    Serial.print(sensorData.pressure);
    Serial.println(" Pa");

    Serial.print("Altitude: ");
    Serial.print(sensorData.altitude);
    Serial.println(" meters");

    Serial.print("Acceleration X: ");
    Serial.print(sensorData.accelX);
    Serial.print(", Y: ");
    Serial.print(sensorData.accelY);
    Serial.print(", Z: ");
    Serial.print(sensorData.accelZ);
    Serial.println(" m/s^2");

    Serial.print("Gyro X: ");
    Serial.print(sensorData.gyroX);
    Serial.print(", Y: ");
    Serial.print(sensorData.gyroY);
    Serial.print(", Z: ");
    Serial.print(sensorData.gyroZ);
    Serial.println(" rad/s");

    Serial.println();
  }
}
