
//Sixteenth step (HHH)

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정

// Define motor interface type
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

void setup() {
  Serial.begin(9600);
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
}

void loop() {
  int move=1000;//모터 이동할 스텝수
  int num=2; //반복할 회전 횟수
  if (Serial.available()>0) {//시리얼 입력 대기
    char command = Serial.read();
    if (command == '1') {
      Serial.println(myStepper.currentPosition());
      myStepper.setMaxSpeed(4000);  // 최대속도 설정 (단위: 스텝/초)
      myStepper.setAcceleration(600); // 가속도 설정 (단위: 스텝/초^2)
      myStepper.setSpeed(600); // 초기 속도 설정 (단위: 스텝/초)
      int i=0;
      while (i<num){
        myStepper.moveTo(move);
        while (myStepper.distanceToGo() != 0){myStepper.run();}delay(100);
        myStepper.moveTo(0);
        while (myStepper.distanceToGo() != 0){ myStepper.run();}delay(100);
        i++;
      }
    }
  }
  myStepper.stop();
  myStepper.disableOutputs();  
}

