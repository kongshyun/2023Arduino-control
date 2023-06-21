/*#include <Servo.h>

Servo servo1;
Servo servo2;

int potPin1 = A0;  // 첫 번째 가변저항의 핀 번호
int potPin2 = A1;  // 두 번째 가변저항의 핀 번호

void setup() {
  servo1.attach(9);  // 첫 번째 서보모터를 9번 핀에 연결
  servo2.attach(10);  // 두 번째 서보모터를 10번 핀에 연결
}

void loop() {
  int val1 = analogRead(potPin1);  // 첫 번째 가변저항의 값을 읽음
  int val2 = analogRead(potPin2);  // 두 번째 가변저항의 값을 읽음

  int angle1 = map(val1, 0, 1023, 0, 180);  // 첫 번째 서보모터의 각도를 변환
  int angle2 = map(val2, 0, 1023, 0, 180);  // 두 번째 서보모터의 각도를 변환

  servo1.write(angle1);  // 첫 번째 서보모터를 설정된 각도로 회전
  servo2.write(angle2);  // 두 번째 서보모터를 설정된 각도로 회전

  delay(15);  // 각도 변경 간의 지연시간 (필요한 경우 조정)
}
*/

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