
#include <DMXSerial.h>
#include <DmxSimple.h>
#include <SoftwareSerial.h>
// Constants for demo program

const int RedPin =    10;  // PWM output pin for Red Light.
const int GreenPin =  9;  // PWM output pin for Green Light.
const int BluePin =   6;  // PWM output pin for Blue Light.
const int SIGNAL =   5; 

// This Example receives the 3 values starting with this channel:
const int startChannel = 0 * 4 + 1;
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() {
  DMXSerial.init(DMXReceiver);
  mySerial.begin(9600);
  // set some default values
  DMXSerial.write(1, 0);
  DMXSerial.write(2, 0);
  DMXSerial.write(3, 0);
  DMXSerial.write(4, 0);

  // enable pwm outputs
  pinMode(5, OUTPUT); // sets the digital pin as output
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}


void loop() {
  
 // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  //mySerial.write('a');
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
  analogWrite(5,   DMXSerial.read(startChannel));
  analogWrite(6, DMXSerial.read(startChannel + 1));
  analogWrite(9,  DMXSerial.read(startChannel + 2));
  analogWrite(10,  DMXSerial.read(startChannel + 3));
  //DMXSerial.init(DMXController);
  DMXSerial.write(5, DMXSerial.read(startChannel + 4));
  DMXSerial.write(6, DMXSerial.read(startChannel + 5));
  DMXSerial.write(7, DMXSerial.read(startChannel + 6));
  DMXSerial.write(8, DMXSerial.read(startChannel + 7));
}

void _LED_Off(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(9, 0);
  analogWrite(10,0);
}