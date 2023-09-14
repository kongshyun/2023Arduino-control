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
 
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);

int Ena = 4;
int Control1=A0;//가변저항 아날로그 핀설정

void setup() {
  pinMode(Ena,OUTPUT);
  pinMode(Control1,INPUT);
  stepper1.setMaxSpeed(1600);
  stepper1.stop();
  stepper1.disableOutputs();
}

void loop() 
{ 
  Control1= analogRead(A0);
  if(Control1>50){
    digitalWrite(Ena,LOW);
    stepper1.setCurrentPosition(0);//위치 초기화
    while(stepper1.currentPosition()!=10){
      Control1= analogRead(A0);
      int motorSpeed1=map(Control1,0,1023,0,1600); 
      stepper1.setSpeed(motorSpeed1);
      stepper1.run();
      if(analogRead(A0)<50){
        digitalWrite(Ena,LOW);
        return;
      }
    }
    
  }
  else{
    digitalWrite(Ena,HIGH);
    stepper1.stop();
    stepper1.disableOutputs();
  }
}