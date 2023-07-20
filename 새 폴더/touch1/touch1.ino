const int touchSensorPin = 2; // 락킹터치 센서의 OUT 핀을 아두이노의 2번 핀에 연결
const int ledPin = 13;        // LED를 아두이노의 13번 핀에 연결
bool ledState = false;        // LED의 상태를 저장하는 변수 (false: 꺼짐, true: 켜짐)
bool touchFlag = false;       // 터치 상태를 저장하는 변수 (false: 터치 안 함, true: 터치 함)

void setup() {
  digitalWrite(ledPin, LOW);
  pinMode(touchSensorPin, INPUT); // 락킹터치 센서의 핀을 입력으로 설정
  pinMode(ledPin, OUTPUT);     // LED의 핀을 출력으로 설정
  
}

void loop() {
  int touchState = digitalRead(touchSensorPin); // 락킹터치 센서의 상태를 읽음

  // 터치를 감지하면 LED 상태를 변경
  if (touchState == HIGH && !touchFlag) {     // 터치되고, 이전에 터치 안한 경우
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    touchFlag = true;
  } else if (touchState == LOW) {            // 터치 안된 경우
    touchFlag = false;
  }
}
