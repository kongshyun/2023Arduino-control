//스텝모터 한번 반복 하는 모션 함수화 코드

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 4;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

int maxSpeed=25000;
int accel=1500;
int setSpeed=10000;  
int move=4000;//모터 이동할 스텝수
int num=2; //반복할 회전 횟수


void setup() {
 //Serial.begin(9600);
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
}

void loop() {
}
