#include<Servo.h>
Servo ser1, ser2, ser3;

int echoArray[5] = {6,4,15,19,17};
int trigArray[5] = {7,5,14,18,16};
int servoArray[3] = {10,9,8};
float serialRandom;

int gateCloseValue = 0;
int gateOpenValue = 100;

int maxDistance = 400;

float duration;
float distance;

int led = 13;

void setup() {
  Serial.begin (9600);
  for(int i = 0; i< sizeof(echoArray)/2; i++){
    pinMode( echoArray[i], INPUT);
    }
  for(int i = 0; i< sizeof(trigArray)/2; i++){
    pinMode( trigArray[i], OUTPUT);
    }
  ser1.attach(servoArray[0]);
  ser2.attach(servoArray[1]);
  ser3.attach(servoArray[2]);

  pinMode(led, OUTPUT);
}

void loop() { 
  mainControl();
 }

void mainBegin(){
    
  
  }

void mainControl(){
  
  if (Serial.available()){
    char ser = Serial.read();
    if(ser == 's'){
      ultrasonicData();
      //sendDataRandom();
      }
    if(ser == 'o'){
      gateOpen();
      lights(ser);
      }
    if(ser == 'c'){
      gateClose();
      lights(ser);
      }
    }
  }

void gateOpen(){
  ser1.write(gateOpenValue);
  ser2.write(gateOpenValue);
  ser3.write(gateOpenValue);
  }

void gateClose(){
  ser1.write(gateCloseValue);
  ser2.write(gateCloseValue);
  ser3.write(gateCloseValue);
  }
  
void sendDataRandom(){
  delay(1000);
  serialRandom = random(10)/2.3; 
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

  float dataSensor[5]= {0,0,0,0,0};

  for(int j = 0; j<sizeof(trigArray)/2; j++){
    for(int i = 0; i< sizeof(trigArray)/2; i++){
      digitalWrite(trigArray[i], LOW);
      delayMicroseconds(2);
      digitalWrite(trigArray[i], HIGH);
      delayMicroseconds(10);
      digitalWrite(trigArray[i], LOW);
      duration = pulseIn(echoArray[i], HIGH);
      distance = duration*0.034/2;
      if(distance > maxDistance){
        dataSensor[i] = dataSensor[i]+2;
        }else{
          dataSensor[i] = dataSensor[i]+ (distance/100);
          }
      }
      delay(100);   
    }
  Serial.println("/////");
  for(int i=0; i< sizeof(dataSensor)/4;i++){
    Serial.print(dataSensor[i]/5);
    Serial.print(",");
    }
  Serial.println(" ");
   }

void lights(char scene){

    if(scene == 'o'){
      digitalWrite(led, HIGH);
      delay(2000);
      digitalWrite(led, LOW);
    }
    else if(scene == 'c'){
  
      for(int i = 0; i<5; i++){
          digitalWrite(led, HIGH);
          delay(100);
          digitalWrite(led, LOW);;
          delay(100);
          }
    }
  }
