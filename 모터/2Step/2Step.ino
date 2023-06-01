#include <AccelStepper.h>
#include <SoftwareSerial.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

// Motor pin definitions
#define mtrPin1  11     // IN1 on the ULN2003 driver 1
#define mtrPin2  10     // IN2 on the ULN2003 driver 1
#define mtrPin3  9     // IN3 on the ULN2003 driver 1
#define mtrPin4  8     // IN4 on the ULN2003 driver 1

#define mtrPin_1  7     // IN1 on the ULN2003 driver 2
#define mtrPin_2  6     // IN2 on the ULN2003 driver 2
#define mtrPin_3  5     // IN3 on the ULN2003 driver 2
#define mtrPin_4  4     // IN4 on the ULN2003 driver 2

AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);
AccelStepper stepper2(HALFSTEP, mtrPin_1, mtrPin_3, mtrPin_2, mtrPin_4);

int speedLeft = 500;
int speedRight = 500;

int leftWheelForeward = 1;
int leftWheelBackward = -1;
int rightWheelForeward = -1;
int rightWheelBackward = 1;

char controlKey = 1;

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(2000.0);
  stepper2.setMaxSpeed(2000.0);
  Serial.println("READY");
}



void loop() {


  switch (controlKey) {
    case 'w': //전진
      _Go();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case 's': //후진
      _Back();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case 'a': //좌회전 전진
      _Left();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case 'd': //우회전 전진
      _Right();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case 'q': //왼쪽 제자리 회전
      _Left360();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case 'e': //오른쪽 제자리 회전
      _Right360();
      Serial.println(controlKey);
      //controlKey = '0';
      break;
    case '1': //정지
      stepper1.stop(); //motor stop
      stepper2.stop();
      stepper1.disableOutputs(); //motor power disconnect, so motor led will turn off
      stepper2.disableOutputs();
      controlKey = '0';
      Serial.println(controlKey);
      break;
    default :
      controlKey = Serial.read();
      break;
  }
}

void _Go() {  //foreward
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 's' || controlKey == 'a' || controlKey == 'd' || controlKey == '1' || controlKey == 'q' || controlKey == 'e')
    {
      return;
    }
  }
}

void _Back() { //Backward
  for (;;) {
    stepper1.move(leftWheelBackward);
    stepper2.move(rightWheelBackward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 'w' || controlKey == 'a' || controlKey == 'd' || controlKey == '1' || controlKey == 'q' || controlKey == 'e')
    {
      return;
    }
  }
}

void _Left() { //Left ForeWard
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(200);
    stepper2.setSpeed(600);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 'w' || controlKey == 's' || controlKey == 'd' || controlKey == '1' || controlKey == 'q' || controlKey == 'e')
    {
      return;
    }
  }
}

void _Right() { //Right ForeWard
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(600);
    stepper2.setSpeed(200);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 'w' || controlKey == 's' || controlKey == 'a' || controlKey == '1' || controlKey == 'q' || controlKey == 'e')
    {
      return;
    }
  }
}

void _Left360() { //Left Quick Trun
  for (;;) {
    stepper1.move(leftWheelBackward);
    stepper2.move(rightWheelForeward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 'w' || controlKey == 's' || controlKey == 'd' || controlKey == '1' || controlKey == 'a' || controlKey == 'e')
    {
      return;
    }
  }
}

void _Right360() { //Right Quick Trun
  for (;;) {
    stepper1.move(leftWheelForeward);
    stepper2.move(rightWheelBackward);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
    //delay(10);
    controlKey = Serial.read();
    if (controlKey == 'w' || controlKey == 's' || controlKey == 'd' || controlKey == '1' || controlKey == 'q' || controlKey == 'a')
    {
      return;
    }
  }
}