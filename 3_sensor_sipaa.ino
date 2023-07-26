
  
 #include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int trigPin = 5;
const int echoPin = 4;

#define SOUND_SPEED 0.033

long duration;
float distanceCm;
const int collision=14;
void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(collision,INPUT);

}

void loop(){

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print("\n");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  int collisionData=digitalRead(collision);
  if(collisionData==0){
    Serial.println("no collision");
  }
  else if(collisionData==1){
    Serial.println("collision");
  }
delay(1000);
  }
  
