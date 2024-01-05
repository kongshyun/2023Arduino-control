#include <ArduinoRS485.h>
#include <ArduinoDMX.h>
#include <AccelStepper.h>

const int universeSize = 16;

int brightness = 0;
int fadeAmount = 1;

const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정

#define motorInterfaceType 1
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin); // 스테퍼모터 핀 정의

unsigned long lastLEDUpdateTime = 0;
unsigned long LEDUpdateTimeInterval = 30;  // Interval for LED dimming in milliseconds

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait forever
  }

  myStepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
}

void loop() {
  int move = 4000; // 모터 이동할 스텝수
  int num = 2;     // 반복할 회전 횟수

  if (Serial.available() > 0) { // 시리얼 입력 대기
    char command = Serial.read();
    if (command == '1') {
      Serial.println(myStepper.currentPosition());
      myStepper.setMaxSpeed(20000);   // 최대속도 설정 (단위: 스텝/초)
      myStepper.setAcceleration(500); // 가속도 설정 (단위: 스텝/초^2)
      myStepper.setSpeed(10000);      // 초기 속도 설정 (단위: 스텝/초)
      int i = 0;
      
      while (i < num) {
        myStepper.moveTo(move);
        while (myStepper.distanceToGo() != 0) {
          myStepper.run();
          updateLED(); // Update LED while the stepper is moving
        }
        delay(100);

        myStepper.moveTo(0);
        while (myStepper.distanceToGo() != 0) {
          myStepper.run();
          updateLED(); // Update LED while the stepper is moving
        }
        delay(100);

        i++;
      }
    }
  }

  myStepper.stop();
  myStepper.disableOutputs();
}

void updateLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastLEDUpdateTime >= LEDUpdateTimeInterval) {
    led_dim(1); // Update LED for channel 1
    lastLEDUpdateTime = currentMillis;
  }
}

void led_dim(int channel) {
  // Your LED dimming code here
  // ...
  DMX.beginTransmission();
  DMX.write(channel, brightness);
  DMX.endTransmission();

  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 80) {
    fadeAmount = -fadeAmount;
  }
  // ...
}
