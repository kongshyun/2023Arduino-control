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
 
int button = 8;
int ena = 4;
int Control1=A1;//가변저항 아날로그 핀설정

void setup() {
  pinMode(ena,INPUT);
  pinMode(button, INPUT);
  stepper1.setMaxSpeed(1600);
  stepper2.setMaxSpeed(1600);
  Serial.begin(9600);
  Serial.println("Hello");
  Serial.println("button  :  " + String(digitalRead(button)));
  stepper1.stop();
  stepper1.disableOutputs();
  stepper2.stop();
  stepper2.disableOutputs();
}

void loop() 
{ 
  
  int button_state=digitalRead(button);
  stepper1.setCurrentPosition(0);//위치 초기화
  while(stepper1.currentPosition()!=800)//Siteeth step일때 10도 움직임.
  {
    Control1= analogRead(A1);
    int motorSpeed1=map(Control1,0,1023,0,1600); 
    stepper1.setSpeed(motorSpeed1);
    stepper1.run();
    if (Control1 < 100){
      stepper1.stop();
      stepper1.disableOutputs();
    }
    if (button_state==1){
      stepper2.setCurrentPosition(0);//위치 초기화
      while(stepper2.currentPosition()!=400){
        stepper2.setSpeed(200); //steps/seconds , 1초에 반바퀴
        stepper2.run();
      }
      return;
      
    }
  }
}