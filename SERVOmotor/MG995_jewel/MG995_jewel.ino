/*
버튼 한번 누르면 정해진 속도로 무한회전
버튼 한번씩 누를때마다 속도 증가
어느정도 속도 오르면 안넘어감

정지버튼누르면 정지.

 */


#include <Servo.h>

Servo servo;
int buttonPin = 2;    // 버튼 핀
int angle = 0;        // 서보모터 각도

void setup() {
  servo.attach(9);    // 서보모터를 아날로그 핀 9에 연결
  pinMode(buttonPin, INPUT);
  servo.write(0);  // 서보모터 각도 설정
}
int angle
void loop() {

  // 버튼을 체크하여 서보모터 동작 제어
  if (digitalRead(buttonPin) == HIGH) {
    delay(500);  // 디바운싱을 위한 지연 시간
    while(digitalRead(buttonPin) == HIGH){
      angle += angle_value;  // 서보모터 각도 10도씩 증가
      if (angle > 180) {
        angle = 0;  // 각도가 180도를 넘어가면 초기화
      }
      servo.write(angle);  // 서보모터 각도 설정
      delay(50);  // 서보모터 동작 안정화를 위한 지연 시간
    
  }
  angle_value=angle_value+3;
}
