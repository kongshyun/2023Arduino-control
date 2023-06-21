#include <Servo.h>

Servo servo;
const int trigPin = 2;    // 초음파 센서의 Trig 핀을 2번 디지털 핀에 연결
const int echoPin = 3;    // 초음파 센서의 Echo 핀을 3번 디지털 핀에 연결
const int servoPin = 9;   // 서보모터의 신호 핀을 9번 디지털 핀에 연결

void setup() {
  servo.attach(servoPin);  // 서보모터 초기화
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // 거리 값에 따라 서보모터 각도 제어
  if (distance > 0 && distance <= 30) {
    int angle = map(distance, 0, 30, 0, 180);  // 거리 값을 0-30 범위의 각도로 변환
    servo.write(angle);  // 서보모터를 지정한 각도로 이동
    delay(15);  // 일시적인 딜레이
  }
}
