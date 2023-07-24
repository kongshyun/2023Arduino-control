const int encoderPinA = 2; // 로터리 엔코더 A상 핀
const int encoderPinB = 3; // 로터리 엔코더 B상 핀
const int buttonPin = 4;   // 로터리 엔코더 스위치 핀

int lastAState = LOW;      // 이전 로터리 엔코더 A상 상태
int lastButtonState = HIGH;   // 이전 버튼 상태
int counter = 0;           // 카운터 값 (회전 방향에 따라 증가 또는 감소)

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // 로터리 엔코더 회전 감지
  int aState = digitalRead(encoderPinA);
  int bState = digitalRead(encoderPinB);
  if (aState != lastAState) {
    if (bState != aState) {
      counter++;
    } else {
      counter--;
    }
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  lastAState = aState;

  // 로터리 엔코더 스위치 버튼 감지
  int buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      Serial.println("Button Pressed!");
    }
  }
  lastButtonState = buttonState;
}
