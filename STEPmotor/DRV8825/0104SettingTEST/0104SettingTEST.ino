
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
// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정
int pre_pos;
int end_pos;
int error;

// Define motor interface type
#define motorInterfaceType 1
#define LED 8
// Creates an instance
AccelStepper stepper1(AccelStepper::DRIVER, stepPin, dirPin);//스테퍼모터 핀 정의
//스텝모터 설정
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
  Serial.println("초기값= 왼쪽: " + String(stepper1.currentPosition())+", 오른쪽: "+String(stepper2.currentPosition())); //현재 스텝각 읽어오기
  State='0';//switch문에서 default로간다.
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  
}

int start_left_position=0;//초기 왼쪽 위치
int start_right_position=0;//초기 오른쪽 위치


void loop() {

  if(Serial.available()){
    char State=Serial.read();
  }
  switch (State) {

    //첫번째 스위치 45도 반복, 다른버튼입력시 원점으로 돌아간 후 실행
    case 'w':
      Serial.println("-----------------State = "+String(State)+"-----------------");
      _Zero();
      for(;;){
        _Go(800,800,Degree45);//Degree45도 위치로 이동
        if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("***BUTTON INPUT!!***");
          return;//for문을 빠져나간다.
        }
        _Go(800,800,0);//0위치로 이동
      }
      break;//switch 문을 빠져나간다.

    //두번째 스위치 90도 반복, 다른버튼입력시 원점으로 돌아간 후 실행
    case 's':
      Serial.println("-----------------State = "+String(State)+"-----------------");
      _Zero();
      for(;;){
        _Go(800,800,Degree90);//Degree90도 위치로 이동
        if(digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5)){
          Serial.println("***BUTTON INPUT!!***");
          return;//for문을 빠져나간다.
        }
        _Go(800,800,0);//0위치로 이동
      }
      break;//switch 문을 빠져나간다.
  
    //세번째 스위치 계속 회전
    case 'a':
      Serial.println("-----------------State = "+String(State)+"-----------------");
      _Zero();
      _Rotation(400,400,1); 
      break;//switch 문을 빠져나간다.
  
    //네번째 스위치 다른속도로 회전
    case 'd':
      Serial.println("-----------------State = "+String(State)+"-----------------");
      _Zero();
      _Rotation(400,400,-1);
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
      return;//함수빠져나가기
    }
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      return;//함수빠져나가기
    }
  }
}

//버튼누르기전까지 계속 한방향으로 회전하는 함수. 한바퀴 돌때마다 스텝각 0으로 초기화 해준다. 그래야 정지 눌렀을때 바로 원점으로 옴.
void _Rotation(int leftspeed,int rightspeed,int Position) {  //foreward
  while((digitalRead(button1)|| digitalRead(button2)||digitalRead(button3)||digitalRead(button4)||digitalRead(button5))!=1){
    stepper1.setSpeed(leftspeed);//모터속도 설정
    stepper2.setSpeed(rightspeed);
    stepper1.move(Position);//모터 이동할 각도 설정
    stepper2.move(Position);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    //한바퀴가 지나면 스텝각 초기화
    if(stepper1.currentPosition()==4096 && stepper2.currentPosition()==4096){
      Serial.println("360!!");
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
    }
    if(stepper1.currentPosition()==-4096 && stepper2.currentPosition()==-4096){
      Serial.println("360!!");
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
    }
  }
}

//원점위치로가는함수
void _Zero(){
  for(;;){
    stepper1.setSpeed(800);//모터속도 설정
    stepper2.setSpeed(800);
    stepper1.moveTo(0);//모터 이동할 각도 설정
    stepper2.moveTo(0);
    stepper1.runSpeedToPosition();//가속없이 현재속도로 실행하는 함수
    stepper2.runSpeedToPosition();
    
    //정해진 위치까지 다 이동했으면 빠져나가기
    if ((stepper1.distanceToGo()==0)and(stepper2.distanceToGo()==0)){
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
      Serial.println("Zero!!");
      return;
    }
  }
}
