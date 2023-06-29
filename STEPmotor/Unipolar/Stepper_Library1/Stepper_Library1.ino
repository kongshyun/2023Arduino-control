// Include the Arduino Stepper Library

/*

4선 유니폴라형 스테펍모터 제어
시리얼 모니터 창에
a입력 -> 시계방향으로 한바퀴
b입력 -> 반시계방향으로 한바퀴

*/

#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;//한바퀴 스텝수

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 3, 4, 6, 7);


void setup()
{
	// set the speed at 60 rpm:
	myStepper.setSpeed(60);
	// initialize the serial port:
	Serial.begin(9600);
}
char state;

void loop() {
  
  if(Serial.available()){
    state=Serial.read();
    if (state=='a'){
      Serial.println(String(state));
      myStepper.step(stepsPerRevolution);
    }
    if (state=='d'){
      Serial.println(String(state));
      myStepper.step(-stepsPerRevolution);
    }
    
  }
}