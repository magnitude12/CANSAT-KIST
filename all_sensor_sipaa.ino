
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>
#include <BH1750.h>
#include <ezButton.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "MQTT_BROKER_IP_ADDRESS";
const char* client_id = "MQ4_Sensor_Client";

const int analog_pin = A0;

Adafruit_MPU6050 mpu;
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
ezButton limitSwitch(14);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) {
  Serial.begin(115200);
  limitSwitch.setDebounceTime(50);
  Serial.println("BEGIN!");
  dht.begin();
  Wire.begin();
  lightMeter.begin();

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // ... Rest of the MPU6050 setup ...

  setup_wifi();
  client.setServer(mqtt_server, 1883);

  delay(100);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  // ... Reading MPU6050, DHT11, BH1750, and limit switch ...

  // MQTT publishing
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // ... Publish sensor data to MQTT ...

  delay(1000);
}
