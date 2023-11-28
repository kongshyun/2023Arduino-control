
 /*
속도단위 steps/seconds
Full Step (LLL): 1바퀴=200스텝
Half Step (HLL): 1바퀴=400스텝
Quarter step (LHL):1바퀴=800스텝
Eighth step (HHL):1바퀴 1600스텝
Sixteenth step (HHH): 1바퀴 3200스텝

*/

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  myStepper.setMaxSpeed(12800);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(5000); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
  myStepper.setSpeed(1000); // 초기 속도 설정 (단위: 스텝/초)
  myStepper.moveTo(1600);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      for(int i=0;i<20;i++){//5번 반복
        while (myStepper.distanceToGo() != 0){
          myStepper.run();
        }
        myStepper.moveTo(-myStepper.currentPosition());
        Serial.print(i);
        delay(500);
      }
    }
  }
}

