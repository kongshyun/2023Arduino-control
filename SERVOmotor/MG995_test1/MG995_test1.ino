#include <Servo.h> //서보관련 라이브러리를 사용하기 위해

Servo servo;  // 서보 변수 선언
int potPin = A0; // 서보 핀
int val;
const int servoPin=10;

void setup() {
  servo.attach(servoPin);//서보모터 핀 초기화
}

void loop() {
  val = analogRead(potPin);//가변저항의 입력을 읽기
  val=map(val,0,1023,0,180);// 입력값을 서보모터의 각도범위로 변환
  servo.write(val);//서보모터를 지정한 각도로 이동
  delay(15);//일시적인 딜레이
}