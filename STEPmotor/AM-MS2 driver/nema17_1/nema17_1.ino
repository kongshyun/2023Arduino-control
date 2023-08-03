#include <Stepper.h>

const int stepsPerRevolution = 200; // 모터 스탭각이 1.8도 이므로 360/1.8=200입력
Stepper myStepper(stepsPerRevolution, 12,11); // 모터의 Dir 핀과 Clk 핀 번호 입력

int DirPIN = 12; // 1번자리
int ClkPIN = 11; // 2번자리
int Sm1PIN = 10; //5번자리
int Sm2PIN = 9; // 6번자리
int EnvPIN = 8; // 8번자리

int a = 0;     //  gen counter (회전수를 기록하는 카운터)
int revDw=2800;
int revUp= 2800; 

void setup() 
{ 
  pinMode(DirPIN, OUTPUT); 
  pinMode(ClkPIN, OUTPUT); 
  pinMode(Sm1PIN, OUTPUT);
  pinMode(Sm2PIN, OUTPUT);
  pinMode(EnvPIN, OUTPUT); 
    
  digitalWrite(DirPIN, HIGH); 
  digitalWrite(ClkPIN, LOW); 
  digitalWrite(Sm1PIN, LOW);  // Set Micro stepping to 1/8
  digitalWrite(Sm2PIN, HIGH);  //스탭모드를 L H(1/8)로 설정
  digitalWrite(EnvPIN, HIGH);   // 모터 구동부 Enable
  
  myStepper.setSpeed(350);// set the motor speed (for multiple steps only):
  Serial.begin(9600);
} 

void loop () {
  if(a<revDw){  
    for(int i=0; i<=revDw; i++)
    {
      myStepper.step(stepsPerRevolution);
      Serial.println(a);
      a++;
    }
  delay(10000); //방향전환전 10초간 정지 
  }
  else if(a>0) {
     for(int i=revUp; i>=0; i--)
     {
      myStepper.step(-stepsPerRevolution);
      a--;
      }
  delay(10000); //다시 10초 정지
  }
}