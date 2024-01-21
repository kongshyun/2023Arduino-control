#include <DMXSerial.h>

#define dmxAddr     1     // dmx starting address
#define ledPin      9     // pin, where the LED is connected

void setup() {
  pinMode(ledPin, OUTPUT);       // initialize digital pin as an output.
  DMXSerial.init(DMXReceiver);   // initialize DMX receiver mode
  DMXSerial.maxChannel(1);       // limit the number of DMX channels to read in
}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();  // Calculate how long no data bucket was received

  if (lastPacket < 5000) {
      digitalWrite(ledPin, HIGH);           // turn the LED on 
      delay(DMXSerial.read(dmxAddr)*1000);  // wait for a number of seconds set through dmx
      digitalWrite(ledPin, LOW);            // turn the LED off 
      delay(1000);                          // wait for a second
   }
  else {
      digitalWrite(ledPin, HIGH);        // turn the LED on 
      delay(1000);                       // wait for a second
      digitalWrite(ledPin, LOW);         // turn the LED off 
      delay(1000);                       // wait for a second
  }                      
}