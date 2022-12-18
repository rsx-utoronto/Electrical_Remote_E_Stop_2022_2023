/*
  Module SX1278 // Arduino UNO/NANO    
    GND         ->   GND
    Vcc         ->   3.3V
    MISO        ->   D12
    MOSI        ->   D11     
    SLCK        ->   D13
    Nss         ->   D10
    Di00        ->   D2
    RST         ->   D9      
 */

#include <SPI.h>
#include <LoRa.h>   
int SIG = 3;

//MAYBECHANGE
String code_off = "3141592653 OFF" 
String code_on = "3141592653 ON"
String inString = "";    // string to hold input
String val = "";


void setup() {
  Serial.begin(9600);
  pinMode(SIG,OUTPUT);
  
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet  
    // Serial.print((char)LoRa.read());
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString;       
    }
    inString = "";     
    LoRa.packetRssi();    
  }
      
  if (val == code_off){
    digitalWrite(SIG, HIGH);
    }
  else if (val == code_on){
    digitalWrite(SIG, LOW);
    }   

}
