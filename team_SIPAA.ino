  
 #include "DHT.h"

#define DHTPIN 2  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int SipaaLED=12;

void setup() {
  Serial.begin(115200); 
  Serial.println("BEGIN!");
  dht.begin();
  pinMode (SipaaLED,OUTPUT);
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print("\n");
  if(t<40){
    digitalWrite(SipaaLED,HIGH);
  }
    else{
      digitalWrite(SipaaLED,LOW);
    }
  
}
