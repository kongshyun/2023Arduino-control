

 /*
속도단위 steps/seconds
Full Step (LLL): 1바퀴=200스텝
Half Step (HLL): 1바퀴=400스텝
Quarter step (LHL):1바퀴=800스텝
Eighth step (HHL):1바퀴 1600스텝
Sixteenth step (HHH): 1바퀴 3200스텝

*/
#include <DMXSerial.h>
#include <DmxSimple.h>
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 4;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

const int num=1; //반복할 회전 횟수
const int STEPS_PER_REV = 200 * 32; // 1/32 스텝 모드일 때 1회전 당 스텝 수 6400
const int revNum=4;


void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.write(7, 0);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  myStepper.setCurrentPosition(0); //스텝모터 초기화
}


void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  int signal=DMXSerial.read(7);
  if (lastPacket < 5000) {
    _LED_Dim();
    if(signal>25 & signal<50){
      _Stepper_move(STEPS_PER_REV * revNum,100, 50);
    }
    else if(signal>5 & signal<76){
      _Stepper_move(STEPS_PER_REV * revNum,200, 100);
    }
    else if(signal>77 & signal<101){
      _Stepper_move(STEPS_PER_REV * revNum,400, 300);
    }
    else if(signal>102 & signal<127){
      _Stepper_move(STEPS_PER_REV * revNum,600, 500);
    }
    else if(signal>128 & signal<153){
      _Stepper_move(STEPS_PER_REV * revNum,1000, 600);
    }
    else if(signal>154 & signal<178){
      _Stepper_move(STEPS_PER_REV * revNum,1500, 1000);
    }
    else if(signal>179 & signal<204){
      _Stepper_move(STEPS_PER_REV * revNum,2000, 1300);
    }
    else if(signal>205 & signal<229){
      _Stepper_move(STEPS_PER_REV * revNum,2500, 1500);
    }
    else if(signal>230 & signal<255){
      _Stepper_move(STEPS_PER_REV * revNum,3000, 2000);
    }
    
  }
  else {
    _LED_Off();
    _Stepper_stop();
  }
}


//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(long int move , int vel, int acel){
  int i=0;
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(vel); // 초기 속도 설정 (단위: 스텝/초)
  while (i<num){
    myStepper.moveTo(move);
    while (myStepper.distanceToGo() != 0){
      _LED_Dim();
      myStepper.run();
    }
    myStepper.moveTo(0);
    while (myStepper.distanceToGo() != 0){ 
      _LED_Dim();
      myStepper.run();
    }
    i++;
  }
}

void _Stepper_stop(){
  myStepper.stop();
  myStepper.disableOutputs();  
}

void _LED_Dim(){
  analogWrite(3,DMXSerial.read(1));
  analogWrite(5, DMXSerial.read(2));
  analogWrite(6, DMXSerial.read(3));
  analogWrite(9, DMXSerial.read(4));
  analogWrite(10,DMXSerial.read(5));
  analogWrite(11,DMXSerial.read(6));
}

void _LED_Off(){
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10,0);
  analogWrite(11,0);
}