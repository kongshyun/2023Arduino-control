/*
  속도단위 steps/seconds
  Full Step (LLL): 1바퀴=200스텝
  Half Step (HLL): 1바퀴=400스텝
  Quarter step (LHL):1바퀴=800스텝
  Eighth step (HHL):1바퀴 1600스텝
  Sixteenth step (HHH): 1바퀴 3200스텝


  리니어 , 모터 1바퀴당 3cm정도 이동
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
const int inpin=6;//포토센서
int val;
int state=1;

void setup() {
  DMXSerial.init(DMXReceiver);
  DMXSerial.write(30, 0);
  myStepper.setCurrentPosition(0); //스텝모터 초기화
  pinMode(inpin,INPUT_PULLUP);
  
  if ((digitalRead(inpin))==1){
    digitalWrite(7,HIGH);delay(500);
    digitalWrite(7,LOW);
  }
  else{
    digitalWrite(7,LOW);
  }

}


void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();
  int signal=DMXSerial.read(30);
  if (lastPacket < 5000) {
    if(state){
    _Stepper_CW_move(260000 ,2000, 1000);
    _Stepper_CCW_move(-6400 ,400, 400);
    } 
    if(signal>127){
      _Stepper_move(200000 ,3000, 1500);
    }  
  }
  else {
    _Stepper_stop();
  }
}

//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_CW_move(long int move , int vel, int acel){
  digitalWrite(7,LOW);
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(100); // 초기 속도 설정 (단위: 스텝/초)
  val=digitalRead(inpin);//포토센서의 값을 읽는다
  myStepper.moveTo(move);
  while (val==1){
    val=digitalRead(inpin);//포토센서의 값을 읽는다
    myStepper.run();
  }
  myStepper.setCurrentPosition(0);
  for (int i=0;i<5;i++){
    digitalWrite(7,HIGH);delay(100);
    digitalWrite(7,LOW);delay(100);
  }
  
}

void _Stepper_CCW_move(long int move , int vel, int acel){
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(100); // 초기 속도 설정 (단위: 스텝/초)
  myStepper.moveTo(move);
  while (myStepper.distanceToGo() != 0){
    myStepper.run();  
  }
  myStepper.setCurrentPosition(0);
  for (int i=0;i<5;i++){
    digitalWrite(7,HIGH);delay(300);
    digitalWrite(7,LOW);delay(300);
  }
  state=0;
}

//스텝모터 구동함수(이동거리, 반복횟수)
void _Stepper_move(long int move , int vel, int acel){
  int i=0;
  myStepper.setMaxSpeed(vel);  // 최대속도 설정 (단위: 스텝/초)
  myStepper.setAcceleration(acel); // 가속도 설정 (단위: 스텝/초^2)
  myStepper.setSpeed(vel); // 초기 속도 설정 (단위: 스텝/초)
  while (i<num){
    myStepper.moveTo(-move);
    while (myStepper.distanceToGo() != 0){
      myStepper.run();
    }
    myStepper.moveTo(0);
    while (myStepper.distanceToGo() != 0){ 
      myStepper.run();
    }
    myStepper.setCurrentPosition(0);
    i++;
  }
  for (int i=0;i<5;i++){
    digitalWrite(7,HIGH);delay(200);
    digitalWrite(7,LOW);delay(200);
  }
}

void _Stepper_stop(){
  myStepper.stop();
  myStepper.disableOutputs();  
}
