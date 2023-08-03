//스텝각 테스트
//Half Step -> 1600 스텝 = 360도 0.225도  / 200 스텝 =
//Quarter Step -> 1600 *2 =360도 0.1125도
//Eighth Step -> 1600*4 = 360도 0.05625도
//Sixteenth Step -> 1600*8 =360도 0.028125도
//
#include <Stepper.h>

const int stepsPerRevolution = 1600; // 모터 스탭각이 1.8도 이므로 360/1.8=200입력
Stepper myStepper(stepsPerRevolution, 12,11); // 모터의 Dir 핀과 Clk 핀 번호 입력

int DirPIN = 12; // 1번자리
int ClkPIN = 11; // 2번자리
int Sm1PIN = 10; //5번자리
int Sm2PIN = 9; // 6번자리
int EnvPIN = 8; // 8번자리

int a = 0;     //  gen counter (회전수를 기록하는 카운터)
int revDw=1;
int revUp= 2800; 

void setup() 
{ 
  pinMode(DirPIN, OUTPUT); 
  pinMode(ClkPIN, OUTPUT); 
  pinMode(Sm1PIN, OUTPUT);
  pinMode(Sm2PIN, OUTPUT);
  pinMode(EnvPIN, OUTPUT); 
    

  /*
     Sm1  Sm2
     H      H  :Half Step
     H      L  :Quarter Step
     L      H  :Eighth Step
     L      L  :Sixteeth Step
  */
  digitalWrite(DirPIN, HIGH); 
  digitalWrite(ClkPIN, LOW); 
  digitalWrite(Sm1PIN, HIGH);  // Set Micro stepping to 1/8
  digitalWrite(Sm2PIN, HIGH);  //스탭모드를 L H(1/8)로 설정
  digitalWrite(EnvPIN, HIGH);   // 모터 구동부 Enable
  
  myStepper.setSpeed(60);// set the motor speed (for multiple steps only):
  Serial.begin(9600);
  delay(3000);
} 
int i=0;
void loop () {
  i++;
  myStepper.step(stepsPerRevolution); //스텝모터 한바퀴
  Serial.println(i);  
  myStepper.step(-stepsPerRevolution); 
  
}