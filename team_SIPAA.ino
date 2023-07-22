const int trigPin = 5;
const int echoPin = 4;
const int sipaaLED=12;
#define SOUND_SPEED 0.033

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sipaaLED,OUTPUT);
 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  Serial.print("Distance (Cm): ");
  Serial.println(distanceCm);
  if(distanceCm<7)
  {
    digitalWrite(sipaaLED,HIGH);
    
  }
  else{
    digitalWrite(sipaaLED,LOW);
    
  }

  
  delay(1000);
}
