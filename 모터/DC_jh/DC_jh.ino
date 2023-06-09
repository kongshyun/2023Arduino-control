// 모터 핀 정의
const int motorPin1 = 2;  // L9110S 드라이버 IN1 핀
const int motorPin2 = 3;  // L9110S 드라이버 IN2 핀

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}
int maxSpeed=255;

void loop() {
  // 속도를 75%로 설정하여 모터 회전 (최대 속도의 75%)
  motorControl(130); // 0부터 255까지의 범위에서 75%에 해당하는 값
  delay(250); // 2초 동안 회전

  //속도를 75%로 설정하여 모터 회전 (최대 속도의 75%)
  motorControl_Revert(130); // 0부터 255까지의 범위에서 75%에 해당하는 값
  delay(1000); // 2초 동안 회전
}

// 모터 제어 함수
void motorControl(int speed) {
  analogWrite(motorPin1, speed);  // IN1 핀에 PWM 신호로 속도 설정
  digitalWrite(motorPin2, LOW);  // IN2 핀 LOW
}

void motorControl_Revert(int speed) {
  analogWrite(motorPin1, LOW);  // IN1 핀에 PWM 신호로 속도 설정
  digitalWrite(motorPin2, speed);  // IN2 핀 LOW
}
                                                                                  