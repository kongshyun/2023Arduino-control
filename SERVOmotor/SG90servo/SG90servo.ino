//SG90서보모터 0~180사이를 angle배열 에 따라 움직이기
#include <Servo.h>

Servo myServo; // Servo 객체 생성
int angle[8]={0,45,90,135,180,135, 90,45,};

void setup() {
  myServo.attach(5); // 5 번핀 사용
}
void loop() {
  for(int i=0;i<8;i++){
    myServo.write(angle[i]);
    delay(2000);
  }
}