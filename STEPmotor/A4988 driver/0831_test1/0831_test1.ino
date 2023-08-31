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
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600);
  Serial.println("hello");
}

void loop() 
{ 
  
    stepper.setCurrentPosition(0);//위치 초기화
    while(stepper.currentPosition() != 200)
    {
      stepper.setSpeed(100); //100steps/seconds , 1초에 반바퀴
      stepper.run();
    }
    Serial.print( "Step  = "  );
    Serial.println(stepper.currentPosition());
    delay(500);
    stepper.setCurrentPosition(0);
    while(stepper.currentPosition() != -200)
    {
      stepper.setSpeed(-100);
      stepper.run();
    }
    Serial.print( "Step  = "  );
    Serial.println(stepper.currentPosition());
    delay(1000);
}