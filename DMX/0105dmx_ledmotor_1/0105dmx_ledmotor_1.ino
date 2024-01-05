/*
  DMX Fade

  This sketch fades the value of DMX channel 1 between 0 and 255 in steps to create a fade effect.
  All other slots are set to a value of 0.

  Circuit:
   - DMX light
   - MKR board
   - MKR 485 shield
     - ISO GND connected to DMX light GND (pin 1)
     - Y connected to DMX light Data + (pin 2)
     - Z connected to DMX light Data - (pin 3)
     - Jumper positions
       - Z \/\/ Y set to ON

  created 5 July 2018
  by Sandeep Mistry

  순차적으로 디밍하는 4개의 LED
*/

#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>

const int universeSize = 16;

int brightness = 0;
int fadeAmount = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  // initialize the DMX library with the universe size
  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait for ever
  }
}

void loop() {
  
  for(int i=1;i<5;i++){
      led_dim(i);
      updateDMX(i, 0);
  }
}


//LED디밍 함수
void led_dim(int channel){
  int count=0;
  while(count<160){
      // set the value of channel
    updateDMX(channel,brightness);

    // change the brightness for the next round
    brightness += fadeAmount;
    count++;
    // reverse fade direction when on edge of range
    if (brightness <= 0 || brightness >= 80) {
      fadeAmount = -fadeAmount;
    }
    // delay for dimming effect
    delay(30);
    
    }
}
void updateDMX(int channel, int value) {
  DMX.beginTransmission();
  DMX.write(channel, value);
  DMX.endTransmission();
}