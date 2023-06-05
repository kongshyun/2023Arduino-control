/*
물그림자 스텝모터 제어
*/

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

char controlKey = 1;// 처음 상태 1로 정지상태.

//스위치 핀 정의
int button1=2;
int button2=3;
int button3=12;
int button4=13;
int button5=A0;

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

//각도별 스텝수 정의
int Degree45=512; //45도
int Degree90=1024; //90도
int Degree180=2048; //180도
int Degree270=3072; //270도
int Degree360 = 4096;//한바퀴 스텝수

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

    //첫번째 스위치
    case 'w': //정해진각도안에서 왔다갔다 반복
      for(int i=0;i<3;i++){
        _CW(800,800,Degree45);//속도 800으로 90도 시계방향 회전
        _CCW(800,800,-Degree45);//속도 800으로 90도 반시계방향 회전
      }
      break;

    //두번째 스위치
    case 's': 
        _CW(800,800,Degree90);//속도 800으로 90도 시계방향 회전
        _CCW(800,800,-Degree90);//속도 800으로 90도 반시계방향 회전
      break;
  
    //세번째 스위치(시계방향으로 세바퀴회전)
    case 'a': 
      _CW(1000,1000,Degree180);
      State='1';
      break;
    case 'd': 
      _CCW(800,800,-Degree360);
      break;
    
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

//시계방향으로 회전
void _CW(int leftspeed,int rightspeed, int degree) {  //foreward
  
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  for(;;){
    stepper1.setSpeed(leftspeed);//모터속도 설정
    stepper2.setSpeed(rightspeed);
    stepper1.moveTo(degree);//모터 이동할 각도 설정
    stepper2.moveTo(degree);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button4)||digitalRead(button5)){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      return;
    }
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      return;
    }
  }
}
  

//반시계방향으로 회전
void _CCW(int leftspeed,int rightspeed, int degree) { //Left ForeWard
  for (;;) {
    stepper1.setSpeed(leftspeed);
    stepper2.setSpeed(rightspeed);
    stepper1.moveTo(degree);
    stepper2.moveTo(degree);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //다른버튼입력이 들어오면 나가기
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button4)||digitalRead(button5)){
      return;
    }
    else if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      State='1';
      return;
    }
  }
}
