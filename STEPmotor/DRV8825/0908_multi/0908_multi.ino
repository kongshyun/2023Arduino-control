/*
스텝모터 2개 압출기용 제어코드

속도단위 steps/seconds
Full Step (LLL): 1바퀴=200스텝
Half Step (HLL): 1바퀴=400스텝
Quarter step (LHL):1바퀴=800스텝
Eighth step (HHL):1바퀴 1600스텝
Sixteenth step (HHH): 1바퀴 3200스텝

*/

#include <AccelStepper.h>
 
#define dirPin1 2
#define stepPin1 3
#define dirPin2 4
#define stepPin2 5
#define dirPin3 6
#define stepPin3 7
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

int motorSpeed=1000;
int Steps=1600;


void setup() {
  stepper1.setMaxSpeed(3200);
  stepper2.setMaxSpeed(3200);
  stepper3.setMaxSpeed(3200);
  stepper4.setMaxSpeed(3200);
  stepper5.setMaxSpeed(3200);
  stepper6.setMaxSpeed(3200);
  Serial.begin(9600);

}


void loop() {
  char command;
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1' ){ // 시리얼 입력 1일 때
      stepper1.setCurrentPosition(0);//위치 초기화
      while(stepper1.currentPosition()!=Steps)//Siteeth step일때 10도 움직임.
      {
        stepper1.setSpeed(motorSpeed);
        stepper1.run();
      }
    }
    else if (command =='2') { 
      stepper2.setCurrentPosition(0);//위치 초기화
      while(stepper2.currentPosition()!=Steps)//Siteeth step일때 10도 움직임.
      {
        stepper2.setSpeed(motorSpeed);
        stepper2.run();
      }
    }
    else if (command =='3') { 
      stepper1.setCurrentPosition(0);//위치 초기화
      stepper2.setCurrentPosition(0);//위치 초기화
      while(stepper2.currentPosition()!=Steps and stepper1.currentPosition()!=Steps)//Siteeth step일때 10도 움직임.
      {
        stepper1.setSpeed(motorSpeed);
        stepper2.setSpeed(motorSpeed);
        stepper1.run();
        stepper2.run();
      }
    }
    else if (command =='4') { 
      stepper1.setCurrentPosition(0);//위치 초기화
      stepper2.setCurrentPosition(0);//위치 초기화
      stepper3.setCurrentPosition(0);//위치 초기화
      while(stepper3.currentPosition()!=Steps and stepper2.currentPosition()!=Steps and stepper1.currentPosition()!=Steps)//Siteeth step일때 10도 움직임.
      {
        stepper1.setSpeed(motorSpeed);
        stepper2.setSpeed(motorSpeed);
        stepper3.setSpeed(motorSpeed);
        stepper1.run();
        stepper2.run();
        stepper3.run();
      }
    }
    else if (command =='5') { 
      stepper1.setCurrentPosition(0);//위치 초기화
      stepper2.setCurrentPosition(0);//위치 초기화
      stepper3.setCurrentPosition(0);//위치 초기화
      stepper4.setCurrentPosition(0);//위치 초기화
      stepper5.setCurrentPosition(0);//위치 초기화
      stepper6.setCurrentPosition(0);//위치 초기화

      while(stepper6.currentPosition()!=Steps and stepper5.currentPosition()!=Steps and stepper4.currentPosition()!=Steps and stepper3.currentPosition()!=Steps and stepper2.currentPosition()!=Steps and stepper1.currentPosition()!=Steps)//Siteeth step일때 10도 움직임.
      {
        stepper1.setSpeed(motorSpeed);
        stepper2.setSpeed(motorSpeed);
        stepper3.setSpeed(motorSpeed);
        stepper4.setSpeed(motorSpeed);
        stepper5.setSpeed(motorSpeed);
        stepper6.setSpeed(motorSpeed);
        stepper1.run();
        stepper2.run();
        stepper3.run();
        stepper4.run();
        stepper5.run();
        stepper6.run();
      }
    }
  }
  else{
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
}
