
#include <DMXSerial.h>
#include <DmxSimple.h>
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 4;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의
const int STEPS_PER_REV = 200 * 32; // 1/32 스텝 모드일 때 1회전 당 스텝 수


void setup() {
  DMXSerial.init(DMXReceiver);
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
    _LED_Dim();
    if(signal>50 & signal<100){
      myStepper.setCurrentPosition(0);
      moveClockwise(STEPS_PER_REV * 200); // 시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
      myStepper.setCurrentPosition(0);
      moveCounterClockwise(STEPS_PER_REV * 200); // 반시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
    }
    //myStepper.setCurrentPosition(0);
    else if(signal>180) {
      myStepper.setCurrentPosition(0);
      moveCounterClockwise(STEPS_PER_REV * 330); // 시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
      myStepper.setCurrentPosition(0);
      moveClockwise(STEPS_PER_REV * 330); // 반시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
    }
    else {
      _LED_Off();
      stopMotor(); // 모터 정지
    }
  }
  else {
    _LED_Off();
    stopMotor(); // 모터 정지
    }
}

void moveClockwise(long steps) {
  myStepper.setMaxSpeed(1000);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(500); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.moveTo(steps);
  myStepper.runToPosition();
}

// 반시계방향으로 주어진 스텝 수만큼 회전하는 함수
void moveCounterClockwise(long steps) {
  myStepper.setMaxSpeed(1000);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(500); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.moveTo(-steps);
  myStepper.runToPosition();
}

void stopMotor() {
  myStepper.stop();
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