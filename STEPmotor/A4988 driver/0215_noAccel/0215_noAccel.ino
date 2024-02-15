//라이브러리를 사용하지 않고 모터 회전.

const int dirPin = 2;  //Dir핀 설정
const int stepPin = 3; //Step핀 설정 

const int stepsPerRevolution = 30000;  
  
void setup()  
{
  Serial.begin(9600);  
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);  
    
}  
int vel=200;
void loop()  
{  
    if (Serial.available()>0) {
    char Signal = Serial.read();
    if (Signal == '1') {
      digitalWrite(dirPin, HIGH);  //시계방향
      for(int i=0; i<4;i++){
        Serial.println("Go Right");
        for(int x = 0; x < stepsPerRevolution; x++)
        {  
            digitalWrite(stepPin, HIGH);  
            delayMicroseconds(vel);  
            digitalWrite(stepPin, LOW);  
            delayMicroseconds(vel);  
        }  
      }
      delay(1000);
      digitalWrite(dirPin, LOW);  //시계방향
      for(int i=0; i<4;i++){
        Serial.println("Go Left");
        for(int x = 0; x < stepsPerRevolution; x++)
        {  
            digitalWrite(stepPin, HIGH);  
            delayMicroseconds(vel);  
            digitalWrite(stepPin, LOW);  
            delayMicroseconds(vel);  
        }  
      }
    }
    else if(Signal=='2'){
      while(1){
        digitalWrite(dirPin, HIGH);  //시계방향
        for(int i=0; i<4;i++){
          Serial.println("Go Right");
          for(int x = 0; x < stepsPerRevolution; x++)
          {  
              digitalWrite(stepPin, HIGH);  
              delayMicroseconds(vel);  
              digitalWrite(stepPin, LOW);  
              delayMicroseconds(vel);  
          }  
        }
        delay(1000);
        digitalWrite(dirPin, LOW);  //시계방향
        for(int i=0; i<4;i++){
          Serial.println("Go Left");
          for(int x = 0; x < stepsPerRevolution; x++)
          {  
              digitalWrite(stepPin, HIGH);  
              delayMicroseconds(vel);  
              digitalWrite(stepPin, LOW);  
              delayMicroseconds(vel);  
          } 
        }
        delay(500);
      }
    }       
  }  
}