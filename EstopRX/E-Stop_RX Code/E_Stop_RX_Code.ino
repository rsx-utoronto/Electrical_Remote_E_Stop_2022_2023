#include <SPI.h>
#include <LoRa.h>   
int SIG = 5;
int LED_ON = 2;
int LED_OFF = 3;

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
//  Serial.println(LoRa.rssi());
//  Serial.println(packetSize);
  
  if (packetSize) { 
    // read packet  
    // Serial.print((char)LoRa.read());
    while (LoRa.available())
    {
//      Serial.println("pog");
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString;       
    }
    inString = "";    
    LoRa.packetRssi(); 
    Serial.println(val); 
      
  }
      
  if (val == code_off){
    digitalWrite(SIG, HIGH);
    digitalWrite(LED_OFF, HIGH);
    digitalWrite(LED_ON, LOW);
//    Serial.println("Off");
    }
  else if (val == code_on){
    digitalWrite(SIG, LOW);
    digitalWrite(LED_OFF, LOW);
    digitalWrite(LED_ON, HIGH);
//    Serial.println("on");
    }   
//  delay(10);
}
