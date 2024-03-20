
#include <DMXSerial.h>
#include <DmxSimple.h>
#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 4;  // Step핀 설정
#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의
const int STEPS_PER_REV = 200 * 32; // 1/32 스텝 모드일 때 1회전 당 스텝 수 6400


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
    if(signal>125 & signal<127){//49~50퍼
      myStepper.setCurrentPosition(0);
      moveClockwise(STEPS_PER_REV * 3,500,100); // 반시계방향 회전
      delay(1000); // 회전 완료 후 1초 대기
      myStepper.setCurrentPosition(0);
      moveCounterClockwise(STEPS_PER_REV *3,500,100 ); //시계방향회전
      delay(1000); // 회전 완료 후 1초 대기
    }
    //myStepper.setCurrentPosition(0);
    else if(signal>130 & signal<140) { //51~54퍼
      myStepper.setCurrentPosition(0);
      moveClockwise(STEPS_PER_REV * 3,1000,500); // 시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
      myStepper.setCurrentPosition(0);
      moveCounterClockwise(STEPS_PER_REV * 3,1000,500); // 반시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
    }
    //myStepper.setCurrentPosition(0);
    else if(signal>178) { //70퍼 이상
      myStepper.setCurrentPosition(0);
      moveClockwise(STEPS_PER_REV * 3,1000,500); // 시계방향으로 20바퀴 회전
      delay(1000); // 회전 완료 후 1초 대기
      myStepper.setCurrentPosition(0);
      moveCounterClockwise(STEPS_PER_REV * 3,1000,500); // 반시계방향으로 20바퀴 회전
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

void moveClockwise(long steps,long vel, long acel) {
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.moveTo(steps);
  myStepper.runToPosition();
}

// 반시계방향으로 주어진 스텝 수만큼 회전하는 함수
void moveCounterClockwise(long steps,long vel, long acel)  {
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
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