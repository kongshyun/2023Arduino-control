// 모터 핀 설정
int ENA=2;
int IN1=3; // [A]
int IN2=4; // [/A]
int ENB=5;
int IN3=6; // [B]
int IN4=7; // [/B]

// 회전 각도 설정
const int stepAngle = 90;  // 90도씩 회전
const int delayTime = 10;  // 5초 대기

void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  digitalWrite(ENA,HIGH);//모터활성화핀
  digitalWrite(ENB,HIGH);
}

void loop() {
  // 시계 방향 회전
  rotateClockwise();
}

// 시계 방향 회전 함수
void rotateClockwise() {
  //     [B]
  // [A]    [/A]
  //    [/B]

  setStepperMotor(1, 0, 0, 1);  // 상태 1
  delay(delayTime);
  setStepperMotor(0, 0, 1, 1);  // 상태 2
  delay(delayTime);
  setStepperMotor(0, 1, 1, 0);  // 상태 3
  delay(delayTime);
  setStepperMotor(1, 1, 0, 0);  // 상태 4
  delay(delayTime);
}

// 반시계 방향 회전 함수
void rotateCounterclockwise() {
  setStepperMotor(1, 1, 0, 0);  // 상태 4
  delay(delayTime);
  setStepperMotor(0, 1, 1, 0);  // 상태 3
  delay(delayTime);
  setStepperMotor(0, 0, 1, 1);  // 상태 2
  delay(delayTime);
  setStepperMotor(1, 0, 0, 1);  // 상태 1
  delay(delayTime);
}

// 스테퍼 모터 상태 설정 함수
void setStepperMotor(const int in1,const int in4,const int in2,const int in3 ) {
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
}
