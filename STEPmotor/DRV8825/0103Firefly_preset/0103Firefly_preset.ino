
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
int pre_pos;
int end_pos;
int error;

// Define motor interface type
#define motorInterfaceType 1
#define LED 8
// Creates an instance
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
  Serial.begin(9600);
  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
}

void loop() {

  //pre_pos=myStepper.currentPosition();
  if (Serial.available()) {
    char command = Serial.read();
    
    if (command == '1') {
      myStepper.setMaxSpeed(4000);  // 최대속도 설정 (단위: 스텝/초)
      myStepper.setAcceleration(300); // 가속도 설정 (단위: 스텝/초^2)
      myStepper.setSpeed(300); // 초기 속도 설정 (단위: 스텝/초)
      myStepper.moveTo(4000);
      for(int i=0;i<3;i++){//5번 반복

        while (myStepper.distanceToGo() != 0){
          myStepper.run();
        }
        
        delay(1000);
        Serial.println("Go");
      }
      delay(1000);
      Serial.println("END");
      }
      /*
      int end_pos=myStepper.currentPosition(); // 구동후 현재 위치를 저장.
      int error=end_pos-pre_pos;
      Serial.println(" error = "+String(error));
      int setMov=error+end_pos;
      Serial.println("")*/
  }
  else if (myStepper.currentPosition()==0){
    Serial.println("STOP");
    myStepper.stop();
    myStepper.disableOutputs();  
  }
  else{
    //초기위치로 이동.
    myStepper.setMaxSpeed(600);  // 최대속도 설정 (단위: 스텝/초)
    myStepper.setAcceleration(0); // 가속도 설정 (단위: 스텝/초^2)
    myStepper.setSpeed(600); // 초기 속도 설정 (단위: 스텝/초)
    myStepper.moveTo(0);
    while (myStepper.distanceToGo() != 0){
        myStepper.run();
    }
  }
}

