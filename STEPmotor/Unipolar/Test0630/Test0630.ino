
/*

4선 유니폴라형 스테펍모터 제어
시리얼 모니터 창에
a입력 -> 시계방향으로 한바퀴
b입력 -> 반시계방향으로 한바퀴

*/

#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution1 = 200;//한바퀴 스텝수
const int stepsPerRevolution2 = 200;//한바퀴 스텝수


// Create Instance of Stepper library
Stepper Stepper1(stepsPerRevolution1, 3, 4, 6, 7);
Stepper Stepper2(stepsPerRevolution2, 8, 9, 10, 11);



void setup()                                                                                                                                                                    
{
	// set the speed at 60 rpm:
	Stepper1.setSpeed(30);     
	// initialize the serial port:
	Serial.begin(9600);
}
char state;

void loop() {
  
  if(Serial.available()){
    state=Serial.read();
    if (state=='a'){
      Serial.println(String(state));
      Stepper1.step(400);
    }
  }
}