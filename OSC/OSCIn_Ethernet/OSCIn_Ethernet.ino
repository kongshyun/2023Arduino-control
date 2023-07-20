#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
//#include <OSCMessage.h>

EthernetUDP Udp;
byte mac[] = {
  0xA8, 0x61, 0x01, 0xAE, 0xE0, 0xA9
};

IPAddress ip(192, 168, 0, 105);
const unsigned int inPort = 8888;

OSCErrorCode error;

const int ledPin = 9;
unsigned int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  Ethernet.begin(mac, ip);
  Udp.begin(inPort);
  Serial.begin(9600);
}

void led(OSCMessage &msg){
  ledState = msg.getInt(0);
  digitalWrite(ledPin, ledState);
  Serial.print("/led: ");
  Serial.println(ledState);
}

void loop() {
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) { 
      msg.dispatch("/led", led);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
