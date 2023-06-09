#include <AccelStepper.h>

// 스텝모터 설정

#define MOTOR_PIN1 11    // 스텝모터의 핀 1
#define MOTOR_PIN2 10   // 스텝모터의 핀 2
#define MOTOR_PIN3 9  // 스텝모터의 핀 3
#define MOTOR_PIN4 8    // 스텝모터의 핀 4
/*
#define MOTOR_PIN1 7    // 스텝모터의 핀 1
#define MOTOR_PIN2 6   // 스텝모터의 핀 2
#define MOTOR_PIN3 5  // 스텝모터의 핀 3
#define MOTOR_PIN4 4    // 스텝모터의 핀 4
*/
AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN1, MOTOR_PIN3, MOTOR_PIN2, MOTOR_PIN4);
const int switchPin = 0;  // 스위치의 핀

void setup() {
  stepper.setMaxSpeed(2000.0);     // 최대 속도 설정
  stepper.setAcceleration(1000.0); // 가속도 설정

  pinMode(switchPin, INPUT_PULLUP); // 내부 풀업 저항 사용

  Serial.begin(9600);
}

void loop() {
stepper.disableOutputs();
  // 스텝모터 회전
  stepper.moveTo(-30);     // 목표 위치 설정
  while (stepper.distanceToGo() != 0) {
    
    stepper.run();
  }
  // 현재 위치 읽어오기
  long currentPosition = stepper.currentPosition();
  Serial.println("현재 위치1: " + String(currentPosition));


}
