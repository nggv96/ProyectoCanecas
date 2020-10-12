

int echoArray[5] = {6,4,15,19,17};
int trigArray[5] = {7,5,14,18,16};
int ledArray[3] = {51,47,43};

int maxDistance = 400;

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
 // receiveData();
  sendData();
 }

void sendData(){
  if (Serial.available()){
    if(Serial.read() == 's'){
      ultrasonicData();
      }
    }
  
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
        dataSensor[i] = dataSensor[i]+4;
        }else{
          dataSensor[i] = dataSensor[i]+ (distance/100);
          }
      }
      delay(200);   
  }
    Serial.println("/////");
    for(int i=0; i< sizeof(dataSensor)/4;i++){
      Serial.print(dataSensor[i]/5);
      Serial.print(",");
      }
    Serial.println(" ");
    }
