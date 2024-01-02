#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   // Dir핀 설정
const int stepPin = 3;  // Step핀 설정

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper stepper(motorInterfaceType, stepPin, dirPin);
// LED 설정
const int ledPin = 6;
float brightness = 0;
float fadeAmount = 1;

void setup() {
  // 스텝모터 및 LED 초기화
  stepper.setMaxSpeed(12800);  // 최대 속도 설정
  stepper.setAcceleration(5000);  // 가속도 설정
  stepper.setCurrentPosition(0); // 현재 위치를 0으로 설정
  stepper.setSpeed(1000); // 초기 속도 설정 (단위: 스텝/초)
  stepper.moveTo(255);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(stepper.currentPosition());
  int i=0;
  while(stepper.distanceToGo()!=0){
    i++;
    stepper.run();
    // LED 밝기 조절
    analogWrite(ledPin, brightness);
    brightness = brightness + (fadeAmount);  // 밝기 증가 또는 감소
    // 밝기가 0 또는 255에 도달하면 방향을 바꿔줍니다.
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount;
    }
  }
  Serial.println(i);
  stepper.moveTo(-stepper.currentPosition());
  while(stepper.distanceToGo()!=0){
    stepper.run();
    // LED 밝기 조절
    analogWrite(ledPin, brightness);

    brightness = brightness + fadeAmount;  // 밝기 증가 또는 감소
    // 밝기가 0 또는 255에 도달하면 방향을 바꿔줍니다.
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount;
    }
  }
}
