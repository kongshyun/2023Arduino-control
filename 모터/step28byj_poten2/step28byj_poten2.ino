/*
 * 스텝모터 시계방향으로 한바퀴, 반시계방향으로 한바퀴
 * <Stepper.h라이브러리 설명>
 * -Stepper stepper(STEPS,IN1,IN2,IN3,IN4):사용하는 Stepper Motor스템수, 각 4핀을 세팅.
 * -stepper.setSpeed(값): Stepper Motor의 속도 설정.
 * -stepper.step(스텝수):스텝 수로 회전각을 표현한다.
 * 스텝모터 한바퀴 스텝각 2048일때 속도 10~14정도가 적당
 * 
 */


//스위치를 누르면 스텝모터 전원 on
//가변저항으로 스텝모터 속도 조절하기 

#include <Stepper.h>
#define STEPS_360 2048 //한바퀴 스텝각

#define STEP_IN1 2
#define STEP_IN2 3
#define STEP_IN3 4
#define STEP_IN4 5

#define STEP2_IN1 6
#define STEP2_IN2 7
#define STEP2_IN3 8
#define STEP2_IN4 9

//스텝모터 선언
Stepper stepper1(STEPS_360, STEP_IN1, STEP_IN3, STEP_IN2, STEP_IN4);       
Stepper stepper2(STEPS_360, STEP2_IN1, STEP2_IN3, STEP2_IN2, STEP2_IN4);       

int Control1=A0;//가변저항 아날로그 핀설정
int Control2=A1;//가변저항 아날로그 핀설정
int motorSpeed1;
int motorSpeed2;


void setup() {
  Serial.begin(9600);
}
void loop() {

  Control1 = analogRead(A0);
  Control2 = analogRead(A1);
  motorSpeed1=map(Control1,0,1023,0,20);
  motorSpeed2=map(Control2,0,1023,0,20);
    stepper1.setSpeed(motorSpeed1); //모터회전속도
    stepper2.setSpeed(motorSpeed2); //모터회전속도

    stepper1.step(-100); // Rotate angle as Steps
    
    stepper2.step(-100); // Rotate angle as Steps
  
  delay(10);
}