//버튼 누르면 10도정도 한번 반복
//버튼 꾹 누르면 계속 반복

#include <Stepper.h>

const int stepsPerRevolution = 200;  // 한 바퀴 스텝 수

Stepper Stepper1(stepsPerRevolution, 3, 4, 6, 7);

const int button = 2;

void setup() {
  pinMode(button, INPUT);
}

void loop() {

  if (digitalRead(button)==1) {
    _Repeat(30,9);
  } else {
    Stepper1.step(0);
  }
}

void _Repeat(int rpm, int steps){
  delay(500);
    Stepper1.setSpeed(rpm);
    Stepper1.step(steps);
    Stepper1.setSpeed(rpm);
    Stepper1.step(-steps);
    delay(500);
}