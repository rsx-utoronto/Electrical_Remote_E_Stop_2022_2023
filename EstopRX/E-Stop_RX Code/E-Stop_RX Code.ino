#include <SPI.h>
#include <LoRa.h>   
int SIG = 3;

//MAYBECHANGE
String code_off = "3141592653 OFF";
String code_on = "3141592653 ON";
String inString = "";    // string to hold input
String val = "";


void setup() {
  Serial.begin(115200);
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
    Serial.println("Off");
    }
  else if (val == code_on){
    digitalWrite(SIG, LOW);
    Serial.println("on");
    }   

}
