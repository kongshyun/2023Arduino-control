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
 
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
 
void setup() {
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() 
{ 
  stepper1.setCurrentPosition(0);//위치 초기화
  stepper2.setCurrentPosition(0);//위치 초기화
  while(stepper2.currentPosition() != 200 and stepper1.currentPosition()!=200)//Siteeth step일때 10도 움직임.
  {
    stepper1.setSpeed(800);
    stepper2.setSpeed(800); //steps/seconds , 1초에 반바퀴
    stepper1.run();
    stepper2.run();
  }
  stepper1.setCurrentPosition(0);//위치 초기화
  stepper2.setCurrentPosition(0);//위치 초기화
  while(stepper2.currentPosition() != -200 and stepper1.currentPosition()!= -200)//Siteeth step일때 10도 움직임.
  {
    stepper1.setSpeed(-200);
    stepper2.setSpeed(-200); //steps/seconds , 1초에 반바퀴
    stepper1.run();
    stepper2.run();
  }
}