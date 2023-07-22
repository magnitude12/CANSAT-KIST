const int trigPin = 5;
const int echoPin = 4;
const int jamesLED=12;
#define SOUND_SPEED 0.033

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(jamesLED,OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  if (distanceCm < 7){
    digitalWrite(jamesLED,HIGH);
  }
else{
  digitalWrite(jamesLED,LOW);
}
  
  delay(1000);
}
