/*
물그림자 스텝모터 2개 제어 TEST2

버튼 5개 역할
-45도 반복
-90도반복
-180도반복
-360도 반시계 방향회전
-정지

++++ 영점맞추기(정지버튼에 넣기)

*/


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

unsigned char State;//모터 상황변수 문자정의.

//각도별 스텝수 정의
int Degree45=512; //45도
int Degree90=1024; //90도
int Degree180=2048; //180도
int Degree270=3072; //270도
int Degree360 = 4096;//한바퀴 스텝수



//초기설정
void setup() {
  
  //모터 최대속도 설정.
  stepper1.setMaxSpeed(2000.0);
  stepper2.setMaxSpeed(2000.0);
  stepper1.setAcceleration(1000.0); // 가속도 설정
  stepper2.setAcceleration(1000.0); // 가속도 설정

  Serial.begin(9600);

  //스위치 핀 INPUT모드로 설정.
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  Serial.println("정지상태= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));//현재 스텝각 읽어오기
  State='0';//switch문에서 default로간다.
}

int start_left_position=stepper1.currentPosition();//초기 왼쪽 위치
int start_right_position=stepper2.currentPosition();//초기 오른쪽 위치

void loop() {

  //스위치 핀 상태 읽어오기
  int button1_state=digitalRead(button1);//전진
  int button2_state=digitalRead(button2);//후진
  int button3_state=digitalRead(button3);//좌회전
  int button4_state=digitalRead(button4);//우회전
  int button5_state=digitalRead(button5);//정지
  delay(15);

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
  controlKey=State;//State 초기값은 0으로 switch문에서 default로 들어간다.

  switch (controlKey) {

    //첫번째 스위치
    case 'w':
      Serial.println(controlKey);
      for(;;){
        Go(Degree45,Degree45);
        if(digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("BUTTON!!");
          return;//for문을 빠져나간다.
        }
      }
      break;//switch 문을 빠져나간다.

    //두번째 스위치
    case 's': 
      Serial.println(controlKey);
      for(;;){
        Go(Degree90,Degree90);
        if(digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("BUTTON!!");
          return;//for문을 빠져나간다.
        }
      }
      break;//switch 문을 빠져나간다.

    //세번째 스위치(180도 시계방향 회전)
    case 'a': 
      

    //네번째 스위치(360도 반시계방향 회전)
    case 'd': 

    case '1': //정지
      Zero();
      long error_left=stepper1.currentPosition();
      long error_right=stepper2.currentPosition();
      Serial.println("State '1' Zero 위치 = 왼쪽: " + String(error_left)+"오른쪽: "+String(error_right));
      //stepper1.moveTo(-error_left);//스텝모터이동할위치설정
      stepper2.moveTo(-error_right);
      while (stepper2.distanceToGo()<-3 && stepper2.distanceToGo()>3) {
        stepper2.run();
        stepper1.run();
        Serial.println("HI");
      }
      Serial.println("erorr복구 Zero 위치 = 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
      State='0';
      break;

    //contorlKey가 0일때는(즉 정지상태일때)switch 문 빠져나감.
    default :
      stepper1.stop(); //motor stop
      stepper2.stop();
      stepper1.disableOutputs();
      stepper2.disableOutputs();
      
      break;
  }
}

//모터움직임함수 Go(왼쪽모터위치, 오른쪽모터위치), 위치는 스텝각으로 넣기
void Go(int LeftPosition, int RightPosition){
  
  long start_left=stepper1.currentPosition();
  long start_right=stepper2.currentPosition();
  Serial.println("Go 시작 위치 = 왼쪽: " + String(start_left)+", 오른쪽: "+String(start_right));

  stepper1.moveTo(LeftPosition);//스텝모터이동할위치설정
  stepper2.moveTo(RightPosition);
  while (stepper1.distanceToGo() != 0 && stepper2.distanceToGo()!=0 ) {
    stepper1.run();
    stepper2.run();
    if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      return;//while문을 빠져나간다.
    }
  }
  stepper2.moveTo(-RightPosition);//스텝모터이동할위치설정
  stepper1.moveTo(-LeftPosition);//스텝모터이동할위치설정
  while (stepper2.distanceToGo() != 0 && stepper1.distanceToGo()!=0 ) {
    stepper2.run();
    stepper1.run();
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      return;//while문을 빠져나간다.
    }
  }
  
}
//원점위치로가는함수
void Zero(){
  stepper1.moveTo(start_left_position);
  stepper2.moveTo(start_right_position);
  while (stepper2.distanceToGo() <3 && stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }
  Serial.println("ZERO!!");
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
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
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
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
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
