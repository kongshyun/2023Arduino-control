
#include <DMXSerial.h>
#include <DmxSimple.h>

// Constants for demo program

const int RedPin =    10;  // PWM output pin for Red Light.
const int GreenPin =  9;  // PWM output pin for Green Light.
const int BluePin =   6;  // PWM output pin for Blue Light.
const int SIGNAL =   5; 

// This Example receives the 3 values starting with this channel:
const int startChannel = 0 * 8 + 1;


void setup() {
  DMXSerial.init(DMXReceiver);

  // enable pwm outputs
  pinMode(5, OUTPUT); // sets the digital pin as output
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}


void loop() {
 // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();

  if (lastPacket < 5000) {
    // read recent DMX values and set pwm levels
    _LED_Dim();

  } else {
    // Show pure red color, when no data was received since 5 seconds or more.
    _LED_Off();
  } 

}

void _LED_Dim(){
  
  //DMXSerial.init(DMXReceiver);
  analogWrite(5,   DMXSerial.read(12));
  analogWrite(6, DMXSerial.read(13));
  analogWrite(9,  DMXSerial.read(14));
  analogWrite(10,  DMXSerial.read(15));
}

void _LED_Off(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10,0);
}