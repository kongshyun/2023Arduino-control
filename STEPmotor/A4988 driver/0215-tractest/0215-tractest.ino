#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

int moveDistance = 32000; // 이동할 스텝 수

void setup() {
  Serial.begin(9600);
  myStepper.setMaxSpeed(1000);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(500); // 가속도 설정 (단위: 스텝/초^2)
}

void loop() {
  if (Serial.available()) {
    char Signal = Serial.read();
    if (Signal == '1') {
      moveLeftRight(moveDistance);
    } else if (Signal == '2') {
      while (true) {
        moveLeftRight(moveDistance);
      }
    }
  }
}

// 왼쪽으로 이동 후 오른쪽으로 이동하는 함수
void moveLeftRight(int steps) {
  // 왼쪽으로 이동
  myStepper.moveTo(-steps);
  myStepper.runToPosition();
  delay(1000); // 이동 완료 후 딜레이
  
  // 오른쪽으로 이동
  myStepper.moveTo(steps);
  myStepper.runToPosition();
  delay(1000); // 이동 완료 후 딜레이
}
