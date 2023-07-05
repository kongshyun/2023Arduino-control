/*
초기상태= 정지
버튼 한번 입력 =30RPM
두번 입력= 60RPM
세번 입력= 120RPM
네번 입력=정지로 다시돌아감

*/

#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;  //한바퀴 스텝수

// Create Instance of Stepper library
Stepper Stepper1(stepsPerRevolution, 3, 4, 6, 7);
//Stepper Stepper2(stepsPerRevolution2, 8, 9, 10, 11);


const int button = 2;
int state = LOW;
int now = LOW;
int prev = LOW;
int count = 0;
int speed = 0;

void setup() {
  pinMode(button, INPUT);
  Serial.begin(9600);
  Serial.println("Hello");
  count = 0;
}


void loop() {
  now = digitalRead(button);
  Serial.println(count);

  if (now - prev == 1) {
    if (count > 2) {
      count = 0;
    } else {
      count++;
    }
  }

  if (count == 0) {
    speed = 1;
    Stepper1.step(0);  //200스텝, 1바퀴

  } else {
    if (count == 1) {
      speed = 30;
    } else if (count == 2) {
      speed = 60;
    } else if (count == 3) {
      speed = 120;
    }
    Stepper1.step(1);  //200스텝, 1바퀴
  }
  Stepper1.setSpeed(speed);
  prev = now;

}