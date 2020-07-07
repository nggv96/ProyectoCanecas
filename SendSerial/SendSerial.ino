
float serialRandom;
int led = 8;

int trigPin = 3;
int echoPin = 4;

long duration;
float distance;

void setup() {
  Serial.begin (9600);
  pinMode(led,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() { 
  sendData();
  receiveData();
 }

void receiveData(){
  if (Serial.available()){
    if(Serial.read() == 'n'){
      digitalWrite(led,HIGH);
      delay(15000);
      digitalWrite(led,LOW);
      }
    }
  }

void sendData(){
  serialRandom = random(10)/2; 
  Serial.println("/////");
  Serial.print(serialRandom);
  Serial.print(",");
  serialRandom = random(10)/2.55;
  Serial.print(serialRandom);
  Serial.print(",");
  serialRandom = random(10)/2.55;
  Serial.print(serialRandom);
  Serial.print(",");
  serialRandom = random(10)/2.55;
  Serial.print(serialRandom);
  Serial.print(",");
  serialRandom = random(10)/2.55;
  Serial.println(serialRandom);
  }

float ultrasonicData(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.println(distance);
  return distance/100;
    }
