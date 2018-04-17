#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

MDNSResponder mdns;
// Replace with your network credentials
const char* ssid = "Belos-Repeater";
const char* password = "Password";
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
String socketan = "111";
String socketaus = "100";

// put your main code here, to run repeatedly:
 const char* schalter[] = {"000101010001010101010","000101010100010101010","000101010101000101010","000101010101010001010","010001010001010101010","010001010100010101010","010001010101000101010","010001010101010001010","010100010001010101010","01010001010000101010","010100010101000101010","010100010101010001010","010101000001010101010","010101000100010101010","010101000101000101010","010101000101010001010"};
 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  
  // if you want to modify body part of html start here
  body = "<h1>Steckdosensteuerung</h1>";
  // socket names and buttons are created dynamical
  for(int i = 0; i < 4; i++){
    body = body + "<h3>Schaltergruppe "+ String(i+1) + " </h3>";
    for(int j = 0; j < 4; j++){
      body = body + "<p>Schalter " + String(j+1) + " <a href=\"group"+String(i+1)+"_socket" + String(j+1) + "On\"><button>AN</button></a>&nbsp;<a href=\"group"+String(i+1)+"_socket" + String(j+1) + "Off\"><button>AUS</button></a></p>";
    }
  }
    body += "</center></body>";
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(2);
 
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connectionwear<<<<<<<<<<<<<<<<<<<<<
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // serial output of connection details
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  // this page is loaded when accessing the root of esp8266´s IP
  server.on("/", [](){
    String webPage = website(header, body);
    server.send(200, "text/html", webPage);
  });
  // Loop ueber die Gruppen
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      String pathOn = "/group"+String(i+1)+"_socket"+String(j+1)+"On";
      const char* pathOnChar = pathOn.c_str();
      String pathOff = "/group"+String(i+1)+"_socket"+String(j+1)+"Off";
      const char* pathOffChar = pathOff.c_str();
      int gruppe = i+1;
      int socket = j+1;
      int magicnumber = (gruppe*4) - (5-socket);
      Serial.println("Gruppe " + String(gruppe) + " und Socket "+String(socket)+" ergibt "+String(magicnumber));
      server.on(pathOnChar, [magicnumber](){
        Serial.println("Suche code " + String(magicnumber));
        String webPage = website(header, body);
        server.send(200, "text/html", webPage);
      String code = String(schalter[magicnumber]) + socketan;
        Serial.println("Sending" + code);
        mySwitch.send(code.c_str());
        delay(1000);
        mySwitch.send(code.c_str());
        delay(1000);
      });
      server.on(pathOffChar, [magicnumber](){
        Serial.println("Suche code " + String(magicnumber));
        String webPage = website(header, body);
        server.send(200, "text/html", webPage);
        String code = String(schalter[magicnumber]) + socketaus;
        Serial.println("Sending " + code);
        mySwitch.send(code.c_str());
        delay(1000);
        mySwitch.send(code.c_str());
        delay(1000);
      });
    }
  }
  server.begin();
  Serial.println("HTTP server started");

  
}

void loop() {
  server.handleClient();

}
