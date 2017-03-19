#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
RCSwitch mySwitch2 = RCSwitch();

MDNSResponder mdns;
// Replace with your network credentials
const char* ssid = "Belos-Repeater";
const char* password = "Wonzen01Herb1";
ESP8266WebServer server(80);

// you can write your own css and html code (head) here
String css = "body {background-color:#ffffff; color: #000000; font-family: 'Century Gothic', CenturyGothic, AppleGothic, sans-serif;}h1 {font-size: 2em;}";
String head1 = "<!DOCTYPE html> <html> <head> <title>Steckdosensteuerung</title> <style>";
String head2 = "</style></head><body><center>";
String header = head1 + css + head2;
String body = "";
String website(String h, String b){
  String complete = h+b;
  return complete;
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(2);
 
  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  String gruppen[] = {"000101010", "010001010", "010100010", "010101000"};
  String schalter[] = {"001010101010", "100010101010", "101000101010", "101010001010"};
  char* an = "111";
  char* aus = "100";

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      String socketan = gruppen[i] + schalter[j] + an;
      String socketaus = gruppen[i] + schalter[j] + aus;
      const char *aktoran = socketan.c_str();
      const char *aktoraus = socketaus.c_str();

      
      
      Serial.println("Schalte Gruppe " + String(i+1) + " Schalter " + String(j + 1) + " an");
      Serial.println(aktoran);
      mySwitch.send(aktoran);
      
      
      delay(2000);
      Serial.println("Schalte Gruppe " + String(i+1) + " Schalter " + String(j + 1) + " aus");
      mySwitch.send(aktoraus);
     
      
      Serial.println(aktoraus);
      delay(2000);
      
    }
  }

}
