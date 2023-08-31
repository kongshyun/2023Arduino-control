#include <Stepper.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

const int stepsPerRevolution = 200;  // 한 바퀴 스텝 수

AccelStepper Stepper1(stepsPerRevolution, 3, 4, 6, 7);

const int button = 2;

void setup() {
  pinMode(button, INPUT);
  Stepper1.setMaxSpeed(2000.0);
  Stepper1.setCurrentPosition(0);
}

void loop() {
  Stepper1.stop(); //motor stop
  if (digitalRead(button)==1) {
    _Go(30,9);
  }
   
  
}
/*
void _Repeat(int rpm){
  delay(500);
    Stepper1.setSpeed(rpm);
    Stepper1.step(9);
    Stepper1.setSpeed(rpm);
    Stepper1.step(-9);
    delay(500);
}*/
void _Go(int leftspeed,int Position) {  //foreward
  for(;;){
    Stepper1.setSpeed(leftspeed);//모터속도 설정
    Stepper1.moveTo(Position);//모터 이동할 각도 설정
    Stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    if(digitalRead(button)==1){
      return;//함수빠져나가기
    }
    //정해진 위치까지 다 이동했으면 빠져나가기
    if (Stepper1.distanceToGo()==0){
      return;//함수빠져나가기
    }
  }
}

//원점위치로가는함수
void _Zero(){
  for(;;){
    Stepper1.setSpeed(100);//모터속도 설정
    Stepper1.moveTo(0);//모터 이동할 각도 설정
    Stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    
    //정해진 위치까지 다 이동했으면 빠져나가기
    if(Stepper1.distanceToGo()==0){
      Stepper1.setCurrentPosition(0);
      Serial.println("Zero!!");
      return;
    }
  }
}