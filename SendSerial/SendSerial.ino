
float serialRandom;
int echoArray[3] = {2,5,8};
int trigArray[3] = {3,6,9};
int ledArray[3] = {4,7,10};
float dataSensor[5];
float duration;
float distance;

void setup() {
  Serial.begin (9600);
  for(int i = 0; i< sizeof(echoArray)/2; i++){
    pinMode( echoArray[i], INPUT);
    }
  for(int i = 0; i< sizeof(trigArray)/2; i++){
    pinMode( trigArray[i], OUTPUT);
    }
  for(int i = 0; i< sizeof(ledArray)/2; i++){
    pinMode( ledArray[i], OUTPUT);
    }
}

void loop() { 
  receiveData();
  ultrasonicData();
 }

void receiveData(){
  if (Serial.available()){
    if(Serial.read() == 'n'){
      for(int i = 0; i< sizeof(ledArray)/2; i++){
        digitalWrite(ledArray[i],HIGH);
        }
      delay(15000);
      for(int i = 0; i< sizeof(ledArray)/2; i++){
        digitalWrite(ledArray[i],LOW);
        }
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

void ultrasonicData(){
  for(int i = 0; i< sizeof(trigArray)/2; i++){
    digitalWrite(trigArray[0], LOW);
    delayMicroseconds(2);
    digitalWrite(trigArray[0], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigArray[0], LOW);
    duration = pulseIn(echoArray[0], HIGH);
    distance = duration*0.034/2;
    dataSensor[i] = distance/100;
    }
    dataSensor[3] = random(10)/2.55;
    dataSensor[4] = random(10)/2.55;
    Serial.println("/////");
    for(int i=0; i< sizeof(dataSensor)/4;i++){
      Serial.print(dataSensor[i]);
      Serial.print(",");
      }
    Serial.println(" ");
    }
