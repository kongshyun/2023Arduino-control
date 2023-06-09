/*
물그림자 스텝모터 2개 제어 TEST2

버튼 5개 역할
-45도 반복
-90도반복
-180도반복
-360도 반시계 방향회전
-정지(원점, 즉 초기위치로 돌아옴)

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
//스위치 핀 정의
int button1=2;
int button2=3;
int button3=12;
int button4=13;
int button5=A0;

char State;//모터 상황변수 문자정의.

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

  Serial.begin(9600);

  //스위치 핀 INPUT모드로 설정.
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  Serial.println("초기값= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));//현재 스텝각 읽어오기
  State='0';//switch문에서 default로간다.
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
}

int start_left_position=stepper1.currentPosition();//초기 왼쪽 위치
int start_right_position=stepper2.currentPosition();//초기 오른쪽 위치

char Zero_state='0';

void loop() {

  //스위치 핀 상태 읽어오기
  int button1_state=digitalRead(button1);//전진
  int button2_state=digitalRead(button2);//후진
  int button3_state=digitalRead(button3);//좌회전
  int button4_state=digitalRead(button4);//우회전
  int button5_state=digitalRead(button5);//정지
  delay(15);//일시 딜레이

  //스위치 입력에 따라 구분하여 State변경
  if (button1_state==1){
    State='w';
    delay(1000);
  }
  //후진
  else if (button2_state==1){
    State='s';
    delay(1000);
  }
  //좌회전
  else if (button3_state==1){
    State='a';
    delay(1000);
  }
  //우회전
  else if (button4_state==1){
    State='d';
    delay(1000);
  }
  else if (button5_state==1){
    State='1';
    delay(1000);
  }

  switch (State) {

    //첫번째 스위치
    case 'w':
      Serial.println("State = "+String(State));
      _Zero();
      for(;;){
        _Go(800,800,Degree45);//속도 800으로 45도 시계방향 회전
        Serial.println("시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        _Go(800,800,0);//속도 800으로 45도 반시계방향 회전
        Serial.println("반시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("BUTTON!!");
          return;//for문을 빠져나간다.
        }
      }
      break;//switch 문을 빠져나간다.

    //두번째 스위치
    case 's':
      Serial.println("State = "+String(State));
      _Zero();
      for(;;){
        _Go(800,800,Degree90);//속도 800으로 90도 시계방향 회전
        Serial.println("시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        _Go(800,800,0);//속도 800으로 45도 반시계방향 회전
        Serial.println("반시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("BUTTON!!");
          return;//for문을 빠져나간다.
        }
      }
      break;//switch 문을 빠져나간다.
  
    //세번째 스위치
    case 'a':
      Serial.println("State = "+String(State));
      _Zero();
      _Rotation(800,800,1);
      Serial.println("시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
      break;//switch 문을 빠져나간다.
  
    //네번째 스위치
    case 'd':
      Serial.println("State = "+String(State));
      _Zero();
      for(;;){
        _Go(800,800,Degree270);//속도 800으로 45도 시계방향 회전
        Serial.println("시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        _Go(800,800,0);//속도 800으로 45도 반시계방향 회전
        Serial.println("반시계후= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
        if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("BUTTON!!");
          return;//for문을 빠져나간다.
        }
      }
      break;//switch 문을 빠져나간다.
  
    case '1': //정지
      _Zero();
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

//정해진 위치까지 가는 함수.
void _Go(int leftspeed,int rightspeed, int Position) {  //foreward
  for(;;){
    stepper1.setSpeed(leftspeed);//모터속도 설정
    stepper2.setSpeed(rightspeed);
    stepper1.moveTo(Position);//모터 이동할 각도 설정
    stepper2.moveTo(Position);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    if(digitalRead(button1)||digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      return;
    }
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      return;
    }
  }
}

//버튼누르기전까지 계속 한방향으로 회전하는 함수. 한바퀴 돌때마다 스텝각 0으로 초기화 해준다. 그래야 정지 눌렀을때 바로 원점으로 옴.
void _Rotation(int leftspeed,int rightspeed,int Position) {  //foreward
  for(;;){
    
    stepper1.setSpeed(leftspeed);//모터속도 설정
    stepper2.setSpeed(rightspeed);
    stepper1.move(Position);//모터 이동할 각도 설정
    stepper2.move(Position);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    //한바퀴가 지나면 스텝각 초기화
    if(stepper1.currentPosition()==4096 && stepper2.currentPosition()==4096){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Zero_state=0;
    }
    else if((stepper1.currentPosition()>2048 && stepper1.currentPosition()<4096)&& (stepper2.currentPosition()<4096 && stepper2.currentPosition()>2048)){
      Serial.println("Revert Zero");
      Zero_state=1;
    }
    else
      Zero_state='0';
    if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
      Serial.println("BUTTON!!");
      return;//for문을 빠져나간다.
    }
   


  }
}
//원점위치로가는함수
void _Zero(){
  Serial.println("Zero_state=  "+String(Zero_state));
  for(;;){
    stepper1.setSpeed(500);//모터속도 설정
    stepper2.setSpeed(500);
    if(Zero_state=='0'){
      stepper1.moveTo(start_left_position);//모터 이동할 각도 설정
      stepper2.moveTo(start_right_position);
    }
    else if (Zero_state=='1'){
      stepper1.moveTo(4096);//모터 이동할 각도 설정
      stepper2.moveTo(4096);
    }
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      Serial.println("원점위치= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Serial.println("Zero!!");
      return;
    }
  }
}
//반바퀴 넘어가면 가까운쪽으로 회전하여 원점으로 돌아간다.
void _ZeroRevert(){
  for(;;){
    stepper1.setSpeed(500);//모터속도 설정
    stepper2.setSpeed(500);
    stepper1.moveTo(4096);//모터 이동할 각도 설정
    stepper2.moveTo(4096);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      Serial.println("원점위치= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition()));
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Serial.println("Revert Zero!!");
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
      State='1';
      return;
    }
  }
}
