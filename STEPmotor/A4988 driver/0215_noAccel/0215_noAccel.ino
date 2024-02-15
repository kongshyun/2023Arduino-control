//라이브러리를 사용하지 않고 모터 회전.

const int dirPin = 2;  //Dir핀 설정
const int stepPin = 3; //Step핀 설정 

const int stepsPerRevolution = 3200*2;  
  
void setup()  
{
  Serial.begin(9600);  
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);  
    
}  
int vel=500;
void loop()  
{  
    digitalWrite(dirPin, HIGH); //반시계방향
    Serial.println("Go Right");
    for(int x = 0; x < stepsPerRevolution; x++)   //한바퀴 스텝(200)반복
    {  
        digitalWrite(stepPin, HIGH);  
        delayMicroseconds(vel);//2000 마이크로초 = 0.002초
        digitalWrite(stepPin, LOW);  
        delayMicroseconds(vel);  
    }  
    delay(1000);   
      
    digitalWrite(dirPin, LOW);  //시계방향
    Serial.println("Go Left");
    for(int x = 0; x < stepsPerRevolution; x++)  //한바퀴 스텝(200)반복
    {  
        digitalWrite(stepPin, HIGH);  
        delayMicroseconds(vel);  
        digitalWrite(stepPin, LOW);  
        delayMicroseconds(vel);  
    }  
    delay(1000);   
}  