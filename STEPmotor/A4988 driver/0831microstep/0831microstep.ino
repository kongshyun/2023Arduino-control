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
#define motorInterfaceType 1
 
AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
AccelStepper stepper2 = AccelStepper(motorInterfaceType, stepPin2, dirPin2);
 
int Control1=A1;//가변저항 아날로그 핀설정
int Control2=A0;//가변저항 아날로그 핀설정
int motorSpeed1=0;
int motorSpeed2=0;

void setup() {
  stepper1.setMaxSpeed(3000);
  stepper2.setMaxSpeed(3000);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() 
{ 
  Control1= analogRead(A1);
  Control2 = analogRead(A0);
  motorSpeed1=map(Control1,0,1023,0,1200);
  motorSpeed2=map(Control2,0,1023,0,1200); 
  if(motorSpeed2>=0 and motorSpeed2<30){
    stepper2.stop();
    stepper2.disableOutputs();
  }
  if(motorSpeed1>=0 and motorSpeed1<30){
    stepper1.stop();
    stepper1.disableOutputs();
  }
  Serial.println("Speed1: "+ String(motorSpeed1)+ ",   Speed2 : " + String(motorSpeed2));
  stepper1.setSpeed(motorSpeed1);
  stepper2.setSpeed(motorSpeed2); //steps/seconds , 1초에 반바퀴
  stepper1.run();
  stepper2.run();
  
  
}