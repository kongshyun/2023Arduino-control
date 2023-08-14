//라이브러리를 사용하지 않고 모터 회전.

const int dirPin = 2;  //Dir핀 설정
const int stepPin = 3; //Step핀 설정 
const int stepsPerRevolution = 200;  
  
void setup()  
{  
    pinMode(stepPin, OUTPUT); 
    pinMode(dirPin, OUTPUT);  
    
}  
void loop()  
{  
    digitalWrite(dirPin, HIGH); //반시계방향
    for(int x = 0; x < stepsPerRevolution; x++)   //한바퀴 스텝(200)반복
    {  
        digitalWrite(stepPin, HIGH);  
        delayMicroseconds(2000);//2000 마이크로초 = 0.002초
        digitalWrite(stepPin, LOW);  
        delayMicroseconds(2000);  
    }  
    delay(1000);   
      
    digitalWrite(dirPin, LOW);  //시계방향
    for(int x = 0; x < stepsPerRevolution; x++)  //한바퀴 스텝(200)반복
    {  
        digitalWrite(stepPin, HIGH);  
        delayMicroseconds(500);  
        digitalWrite(stepPin, LOW);  
        delayMicroseconds(500);  
    }  
    delay(1000);   
}  