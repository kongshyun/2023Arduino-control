// 모터 핀 설정
int motorPins[] = {3, 5,6,9};  // 모터의 PWM 핀

// 모터 속도 설정
int motorSpeeds[] = {60, 250 ,90,150};  // 각 모터의 초기 속도 (0~255 범위)


void setup() {
  // 모터 핀을 출력으로 설정
  for (int i = 0; i < 4; i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

void loop() {
  // 4개의 모터를 순환하며 속도 조절
  for (int i = 0; i < 4; i++) {
    analogWrite(motorPins[i], motorSpeeds[i]);  // 해당 모터의 속도 설정
    delay(1000);  // 1초 동안 유지

    // 다음 모터로 넘어가기 전에 이전 모터를 정지
    analogWrite(motorPins[i], 0);
    delay(500);  // 0.5초 동안 유지
  }
}
