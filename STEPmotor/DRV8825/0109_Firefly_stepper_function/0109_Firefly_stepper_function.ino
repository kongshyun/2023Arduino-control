//스텝모터 한번 반복 하는 모션 함수화 코드

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

int maxSpeed=25000;
int accel=1500;
int setSpeed=10000;  
int move=4000;//모터 이동할 스텝수
int num=2; //반복할 회전 횟수


void setup() {
  Serial.begin(9600);
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
}

void loop() {
  if (Serial.available()>0) {//시리얼 입력 대기
    char command = Serial.read();
    if (command == '1') {
      _Stepper_move(move,num);
    }
  }
  _Stepper_stop();//모터정지 및 전원차단
}



//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(int move , int num){
  myStepper.setMaxSpeed(maxSpeed);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(accel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(setSpeed); // 초기 속도 설정 (단위: 스텝/초)
  int i=0;
  while (i<num){
    myStepper.moveTo(move);
    while (myStepper.distanceToGo() != 0){myStepper.run();}delay(100);
    myStepper.moveTo(0);
    while (myStepper.distanceToGo() != 0){ myStepper.run();}delay(100);
    i++;
  }
}

void _Stepper_stop(){
  myStepper.stop();
  myStepper.disableOutputs();  
}