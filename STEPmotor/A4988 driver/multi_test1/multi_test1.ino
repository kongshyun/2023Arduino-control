/*
스텝모터 제어코드
1바퀴=200스텝
속도단위 steps/seconds = 0.3 rpm,    60rpm=200steps/seconds
*/

#include <AccelStepper.h>
 
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
const int steps[ ]={30,40,100,0,150,200,400};//스텝수 배열
const int speed[ ]={50,100,100,0,100,60,50};//속도배열
const int time[ ]={1000,1000,1000,5000,1000,1000};//지연시간배열
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin); //핀설정
int i=0; 
void setup() {
  stepper.setMaxSpeed(1000);
  
}

void loop() {
  stepper.setCurrentPosition(0);
  if(i>7) i=0;
  while(stepper.currentPosition() != steps[i])
  {
    stepper.setSpeed(speed[i]);
    stepper.runSpeed();
  }
  
  delay(time[i]);
  i++;
}