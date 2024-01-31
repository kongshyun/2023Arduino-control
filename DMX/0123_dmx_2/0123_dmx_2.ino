
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
const int move=4000;//모터 이동할 스텝수
const int num=2; //반복할 회전 횟수

// Constants for demo program

const int RedPin =    10;  // PWM output pin for Red Light.
const int GreenPin =  9;  // PWM output pin for Green Light.
const int BluePin =   6;  // PWM output pin for Blue Light.
const int SIGNAL =   5; 

// This Example receives the 3 values starting with this channel:
const int startChannel = 0 * 17 + 1;


void setup() {
  DMXSerial.init(DMXReceiver);
// set some default values
  DMXSerial.write(5, 0);
  DMXSerial.write(6, 0);
  DMXSerial.write(9, 0);
  DMXSerial.write(10, 0);
  // enable pwm outputs
  pinMode(5, OUTPUT); // sets the digital pin as output
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  myStepper.setCurrentPosition(0); //스텝모터 초기화

}


void loop() {
 // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels
    _LED_Dim();
    int signal=DMXSerial.read(16);
    if(signal>150){
      _Stepper_move(move,num);
    }
    else {
    _LED_Dim();
    _Stepper_stop();
    }
  }
}


//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(int move , int num){
  myStepper.setMaxSpeed(maxSpeed);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(accel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(setSpeed); // 초기 속도 설정 (단위: 스텝/초)
  int i=0;
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
  
  //DMXSerial.init(DMXReceiver);
  analogWrite(5,   DMXSerial.read(5));
  analogWrite(6, DMXSerial.read(6));
  analogWrite(9,  DMXSerial.read(7));
  analogWrite(10,  DMXSerial.read(8));
}

void _LED_Off(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10,0);
}