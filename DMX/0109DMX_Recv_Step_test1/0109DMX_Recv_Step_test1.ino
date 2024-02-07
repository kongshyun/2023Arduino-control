// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialRecv.ino: Sample DMX application for retrieving 3 DMX values:
// address 1 (red) -> PWM Port 9
// address 2 (green) -> PWM Port 6
// address 3 (blue) -> PWM Port 5
//
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
//
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// 28.12.2011 changed to channels 1..3 (RGB) for compatibility with the DmxSerialSend sample.
// 10.05.2012 added some lines to loop to show how to fall back to a default color when no data was received since some time.
// - - - - -

#include <DMXSerial.h>

// Constants for demo program

const int RedPin =    10;  // PWM output pin for Red Light.
const int GreenPin =  9;  // PWM output pin for Green Light.
const int BluePin =   6;  // PWM output pin for Blue Light.
const int SIGNAL =   5; 

// This Example receives the 3 values starting with this channel:
const int startChannel = 0 * 3 + 1;

//초기값 
#define RedDefaultLevel   0
#define GreenDefaultLevel 0
#define BlueDefaultLevel  0

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의

const int maxSpeed=25000;
const int accel=1500;
const int setSpeed=10000;  
const int move=2000;//모터 이동할 스텝수
const int num=2; //반복할 회전 횟수

void setup() {
  DMXSerial.init(DMXReceiver);

  // set some default values
  DMXSerial.write(1, 0);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);
  // enable pwm outputs
  pinMode(RedPin,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin,  OUTPUT);
  pinMode(SIGNAL,OUTPUT);
  myStepper.setCurrentPosition(0); //스텝모터 초기화
}


void loop() {
 // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();

  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels
    analogWrite(RedPin,   DMXSerial.read(startChannel));
    analogWrite(GreenPin, DMXSerial.read(12));
    analogWrite(BluePin,  DMXSerial.read(13));
    int signal=DMXSerial.read(startChannel);

    if(signal>150){
      _Stepper_move(move,num);
    }

  } else {
    // Show pure red color, when no data was received since 5 seconds or more.
    analogWrite(RedPin,   RedDefaultLevel);
    analogWrite(GreenPin, GreenDefaultLevel);
    analogWrite(BluePin,  BlueDefaultLevel);
    _Stepper_stop();
  } 

}


//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(int move , int num){
  myStepper.setMaxSpeed(maxSpeed);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(accel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(setSpeed); // 초기 속도 설정 (단위: 스텝/초)
  int i=0;
  while (i<num){
    analogWrite(RedPin,   DMXSerial.read(startChannel));
    analogWrite(GreenPin, DMXSerial.read(startChannel + 1));
    analogWrite(BluePin,  DMXSerial.read(startChannel + 2));
    myStepper.moveTo(move);
    while (myStepper.distanceToGo() != 0){myStepper.run();}delay(100);
    myStepper.moveTo(0);
    while (myStepper.distanceToGo() != 0){ myStepper.run();}delay(100);
    i++;
  }
}

void _Stepper_stop(){
    myStepper.stop();
    myStepper.disableOutputs();  
}
