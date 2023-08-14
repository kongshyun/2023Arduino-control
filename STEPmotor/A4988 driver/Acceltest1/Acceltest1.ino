//AccelStepper라이브러리를 활용한 스텝모터 제어.

#include <AccelStepper.h>

// Define pin connections
const int dirPin = 2;   //Dir핀 설정
const int stepPin = 3;  //Step핀 설정

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
	myStepper.setMaxSpeed(2000);
	myStepper.setAcceleration(50);
  myStepper.setCurrentPosition(0);
	myStepper.setSpeed(200);
	myStepper.moveTo(200);
}

void loop() {
	// Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) 
		myStepper.moveTo(-myStepper.currentPosition());

	// Move the motor one step
	myStepper.run();
}