/*
 *
 */
#include <AccelStepper.h>

#define dirPin1 2
#define stepPin1 3

#define dirPin2 4
#define stepPin2 5
#define dirPin3 6
#define stepPin3 17
#define dirPin4 8
#define stepPin4 9
#define dirPin5 10
#define stepPin5 11
#define dirPin6 12
#define stepPin6 13


AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);
AccelStepper stepper4(AccelStepper::DRIVER, stepPin4, dirPin4);
AccelStepper stepper5(AccelStepper::DRIVER, stepPin5, dirPin5);
AccelStepper stepper6(AccelStepper::DRIVER, stepPin6, dirPin6);

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(3200);
  stepper2.setMaxSpeed(3200);
  stepper3.setMaxSpeed(3200);
  stepper4.setMaxSpeed(3200);
  stepper5.setMaxSpeed(3200);
  stepper6.setMaxSpeed(3200);
}

void loop() {
  stopMotors(); // 모터 정지
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case '1': // 시리얼 입력 1일 때
        startMotors(); // 모터 시작
        break;
      case '2': // 시리얼 입력 2일 때
        stopMotors(); // 모터 정지
        break;
      default:
        // 아무 동작도 하지 않음
        stopMotors(); // 모터 정지
        break;
    }
  }
}

void startMotors() {
  stepper1.setSpeed(1000);
  stepper1.run();
  
  stepper2.setSpeed(1000);
  stepper2.run();
  
  stepper3.setSpeed(1000);
  stepper3.run();
  
  stepper4.setSpeed(1000);
  stepper4.run();
  
  stepper5.setSpeed(1000);
  stepper5.run();
  
  stepper6.setSpeed(1000);
  stepper6.run();
}

void stopMotors() {
  stepper1.stop();
  stepper1.disableOutputs();
  stepper2.stop();
  stepper2.disableOutputs();
  stepper3.stop();
  stepper3.disableOutputs();
  stepper4.stop();
  stepper4.disableOutputs();
  stepper5.stop();
  stepper5.disableOutputs();
  stepper6.stop();
  stepper6.disableOutputs();
}
