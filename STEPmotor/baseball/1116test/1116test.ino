/*
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
 
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
 
void setup() {
  stepper1.setMaxSpeed(1000);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() 
{ 
  stepper1.setCurrentPosition(0);//위치 초기화
  while(stepper1.currentPosition()!=400)//Siteeth step일때 10도 움직임.
  {
    stepper1.setSpeed(800);
    stepper1.run();
  }
  stepper1.setCurrentPosition(0);//위치 초기화
  while(stepper1.currentPosition()!= -400)//Siteeth step일때 10도 움직임.
  {
    stepper1.setSpeed(-800);
    stepper1.run();
  }
}