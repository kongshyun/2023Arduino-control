
#include <DMXSerial.h>
#include <DmxSimple.h>
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 4;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

const int maxSpeed=25000;
const int accel=1500;
const int setSpeed=10000;  
const int move=2000;//모터 이동할 스텝수
const int num=1; //반복할 회전 횟수



void setup() {
  DMXSerial.init(DMXReceiver);
  // // enable pwm outputs
  // pinMode(5, OUTPUT); // sets the digital pin as output
  DMXSerial.write(16, 0);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  myStepper.setCurrentPosition(0); //스텝모터 초기화

}


void loop() {
 // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  int signal=DMXSerial.read(16);
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels
    _LED_Dim();
    if(signal>50 & signal<100){
      _Stepper_move(move,1000, num);
    }
    else if(signal>180){
      _Stepper_move(move,200, num);
    }
  }
  else {
    _LED_Off();
    _Stepper_stop();
  }
}


//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(int move , int vel, int num){
  int i=0;
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(vel); // 가속도 설정 (단위: 스텝/초^2)
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