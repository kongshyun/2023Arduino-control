#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   //Dir핀 설정
const int stepPin = 3;  //Step핀 설정

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(2000);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(100); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
  myStepper.setSpeed(200); // 초기 속도 설정 (단위: 스텝/초)
  myStepper.moveTo(-3600); // 반시계 방향으로 5바퀴 회전 (3600스텝 * 5)
}

void loop() {
  // Change direction once the motor reaches target position
  if (myStepper.distanceToGo() == 0) {
    myStepper.moveTo(-myStepper.currentPosition());
  }

  // Move the motor one step
  myStepper.run();
}