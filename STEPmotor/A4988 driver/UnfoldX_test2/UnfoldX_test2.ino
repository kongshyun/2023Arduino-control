/*
스텝모터 제어코드
1바퀴=200스텝
속도단위 steps/seconds
*/

#include <AccelStepper.h>
 
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
 
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
 
void setup() {
  stepper.setMaxSpeed(1000);
}

void loop() 
{ 
  for(int i=0;i<5;i++){
    stepper.setCurrentPosition(0);
    while(stepper.currentPosition() != 100)
    {
      stepper.setSpeed(200); // 200 steps/seconds
      stepper.run();
    }
    stepper.setCurrentPosition(0);
    while(stepper.currentPosition() != -100)
    {
      stepper.setSpeed(-200); // 200 steps/seconds
      stepper.runSpeed();
    }
  }
}