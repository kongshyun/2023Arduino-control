#include <Servo.h> //서보관련 라이브러리를 사용하기 위해

Servo sg90;  // 서보 변수 선언
int potPin = 0; // 서보 핀
int val;

void setup() {
  sg90.attach(10);
}

void loop() {
  val = analogRead(potPin);//작은서보모터
  val=map(val,0,1023,0,179);
  sg90.write(val);
}

