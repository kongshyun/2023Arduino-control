//스텝모터 2개 상황별 제어
//5개의 스위치로 상황 설정(전진, 후진, 좌회전, 우회전 ,정지)

#include <AccelStepper.h>
#include <SoftwareSerial.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

//모터 핀번호 정의
#define mtrPin1  11     // IN1 on the ULN2003 driver 1
#define mtrPin2  10     // IN2 on the ULN2003 driver 1
#define mtrPin3  9     // IN3 on the ULN2003 driver 1
#define mtrPin4  8     // IN4 on the ULN2003 driver 1

#define mtrPin_1  7     // IN1 on the ULN2003 driver 2
#define mtrPin_2  6     // IN2 on the ULN2003 driver 2
#define mtrPin_3  5     // IN3 on the ULN2003 driver 2
#define mtrPin_4  4     // IN4 on the ULN2003 driver 2

//스텝모터 설정
AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);
AccelStepper stepper2(HALFSTEP, mtrPin_1, mtrPin_3, mtrPin_2, mtrPin_4);


int speedLeft = 500;
int speedRight = 500;


int leftWheelForeward = 1;
int leftWheelBackward = -1;
int rightWheelForeward = -1;
int rightWheelBackward = 1;

char controlKey = 1;// 처음 상태 1로 정지상태.

//스위치 핀 정의
int button1=2;//전진
int button2=3;//후진
int button3=12;//좌회전
int button4=13;//우회전
int button5=A0;//정지

//초기설정
void setup() {
  
  //모터 최대속도 설정.
  stepper1.setMaxSpeed(2000.0);
  stepper2.setMaxSpeed(2000.0);
  Serial.begin(9600);

  //스위치 핀 INPUT모드로 설정.
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
}

unsigned char State;//모터 상황변수 문자정의.

void loop() {

  //스위치 핀 상태 읽어오기
  int button1_state=digitalRead(button1);//전진
  int button2_state=digitalRead(button2);//후진
  int button3_state=digitalRead(button3);//좌회전
  int button4_state=digitalRead(button4);//우회전
  int button5_state=digitalRead(button5);//정지
  delay(10);

  //스위치 입력에 따라 구분하여 State변경
  if (button1_state==1){
    State='w';
  }
  //후진
  else if (button2_state==1){
    State='s';
  }
  //좌회전
  else if (button3_state==1){
    State='a';
  }
  //우회전
  else if (button4_state==1){
    State='d';
  }
  else if (button5_state==1){
    State='1';
  }

  //State값에따라 모터 상황 설정 변수contorlkey 에 넣기.
  controlKey=State;

  //controlKey값에 따라 case별로 함수 실행.
  switch (controlKey) {
    case 'w': //전진
      Serial.println(controlKey);
      _Go();
      
      //controlKey = '0';
      break;
    case 's': //후진
      Serial.println(controlKey);
      _Back();
      
      //controlKey = '0';
      break;
    case 'a': //좌회전 전진
      Serial.println(controlKey);
      _Left();
      
      //controlKey = '0';
      break;
    case 'd': //우회전 전진
      Serial.println(controlKey);
      _Right();
      
      //controlKey = '0';
      break;/*
    case 'q': //왼쪽 제자리 회전
      Serial.println(controlKey);
      _Left360();
      
      //controlKey = '0';
      break;
    case 'e': //오른쪽 제자리 회전
      Serial.println(controlKey);
      _Right360();
      
      //controlKey = '0';
      break;
      */
    case '1': //정지
      stepper1.stop(); //motor stop
      stepper2.stop();
      stepper1.disableOutputs();
      stepper2.disableOutputs();
      controlKey = '0';
      break;

    //contorlKey가 0일때는(즉 정지상태일때)switch 문 빠져나감.
    default :
      break;
  }
}

void _Go() {  //foreward
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //다른버튼입력이 들어오면 나가기
    if(digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      return;
    }
  }
}

void _Back() { //Backward
  for (;;) {
    stepper1.move(leftWheelBackward);
    stepper2.move(rightWheelBackward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //다른버튼입력이 들어오면 나가기
    if(digitalRead(button1)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      return;
    }
  }
}

void _Left() { //Left ForeWard
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(200);
    stepper2.setSpeed(600);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //다른버튼입력이 들어오면 나가기
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button4)||digitalRead(button5)){
      return;
    }
  }
}

void _Right() { //Right ForeWard
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(600);
    stepper2.setSpeed(200);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //다른버튼입력이 들어오면 나가기
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button3)||digitalRead(button5)){
      return;
    }
  }
}
/*
void _Left360() { //Left Quick Trun
  for (;;) {
    stepper1.move(leftWheelBackward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
  }
}

void _Right360() { //Right Quick Trun
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelBackward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
  }
}*/