/*
  Example for receiving
  
  https://github.com/sui77/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
RCSwitch mySwitch1 = RCSwitch();
RCSwitch mySwitch2 = RCSwitch();
RCSwitch mySwitch3 = RCSwitch();


void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableReceive(1); 
  mySwitch.enableReceive(2); 
  mySwitch.enableReceive(3); 
  Serial.println("Hallo!");
}

void loop() {
  if (mySwitch.available()) {
    Serial.println("Button pressed");
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
  if (mySwitch1.available()) {
    Serial.println("1 Button pressed");
    mySwitch1.resetAvailable();
  }
  if (mySwitch2.available()) {
    Serial.println("2 Button pressed");
    mySwitch2.resetAvailable();
  }
  if (mySwitch3.available()) {
    Serial.println("3 Button pressed");
    mySwitch3.resetAvailable();
  }
}
