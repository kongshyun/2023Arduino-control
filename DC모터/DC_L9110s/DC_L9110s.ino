// 모터 핀 정의
const int motorPin1 = 2;  // L9110S 드라이버 IN1 핀
const int motorPin2 = 3;  // L9110S 드라이버 IN2 핀
const int motorPin3 = 4;  // L9110S 드라이버 IN1 핀
const int motorPin4 = 5;  // L9110S 드라이버 IN2 핀

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}
int maxSpeed=255;//속도 130아래로 안떨어짐

void loop() {

  motorControl(130,1000);//정방향
  motorControl_Stop(1000);
  motorControl_Revert(130,1000);//역방향
  motorControl_Stop(1000);

}

//시계방향회전(속도, 시간)
void motorControl(int speed, int time) {
  analogWrite(motorPin1, speed);  // IN1 핀에 PWM 신호로 속도 설정
  digitalWrite(motorPin2, LOW);  // IN2 핀 LOW
  delay(time);
}

//반시계방향회전
void motorControl_Revert(int speed,int time) {
  analogWrite(motorPin1, LOW);  // IN1 핀에 PWM 신호로 속도 설정
  digitalWrite(motorPin2, speed);  // IN2 핀 LOW
  delay(time);
}

//정지
void motorControl_Stop(int time) {
  analogWrite(motorPin1, LOW);  // IN1 핀에 PWM 신호로 속도 설정
  digitalWrite(motorPin2, LOW);  // IN2 핀 LOW
  delay(time);
}
                                                                                                                                                       