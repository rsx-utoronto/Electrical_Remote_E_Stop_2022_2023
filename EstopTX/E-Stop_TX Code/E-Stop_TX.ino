#include <Arduino.h>
#include <LoRa.h>
#include <OneButton.h>
#include <avr/wdt.h>

#include "enums.h"
#include "settings.h"


mode currentMode = ROVER_ON;
long timeOfLastTx = 0;        // in ms

OneButton on_btn(ON_SW_PIN, true);
OneButton off_btn(OFF_SW_PIN, true);
int Sig_pin = 7;

void sendState() {
  Serial.println("Sending state");
  LoRa.beginPacket();

  if (currentMode == ROVER_OFF) {
    Serial.println("Sending ROVER OFF!");
    LoRa.print(ROVER_OFF_MAGIC);
  }
  else if (currentMode == ROVER_ON) {
    Serial.println("Sending ROVER ON!");
    LoRa.print(ROVER_ON_MAGIC);
  }

  Serial.println("ENDING PACKET!");
  LoRa.endPacket();
  // return LoRa.endPacket();
}

void off_btn_click() {
  Serial.println("ROVER OFF");
  currentMode = ROVER_OFF;
  sendState();

  digitalWrite(OFF_LED_PIN, HIGH);  // turn on "OFF" LED
  digitalWrite(ON_LED_PIN, LOW);
  digitalWrite(Sig_pin, HIGH);
  LoRa.beginPacket();
  LoRa.print("3141592653 OFF");
  LoRa.endPacket();
}

void on_btn_click() {
  Serial.println("ROVER ON");
  currentMode = ROVER_ON;
  sendState();

  digitalWrite(ON_LED_PIN, HIGH);  // turn on "ON" LED
  digitalWrite(OFF_LED_PIN, LOW);
  digitalWrite(Sig_pin, LOW);
  LoRa.beginPacket();
  LoRa.print("3141592653 ON");
  LoRa.endPacket();
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello world!");

  // set up LoRa
  LoRa.setSPIFrequency(500000);
  bool status = LoRa.begin(433E6);          // 433 MHz
//  LoRa.setTxPower(TX_POWER);

  if (!status) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  Serial.println("LoRa OK!");

  pinMode(ON_LED_PIN, OUTPUT);
  pinMode(OFF_LED_PIN, OUTPUT);
  pinMode(Sig_pin, OUTPUT);

  on_btn.attachClick(on_btn_click);
  off_btn.attachClick(off_btn_click);

  digitalWrite(ON_LED_PIN, HIGH);   // turn on "ON" LED
  digitalWrite(OFF_LED_PIN, LOW);
  
  wdt_disable();
  delay(3000);
  wdt_enable(WDTO_2S);
}

void loop() {

  // Send state if time is up
  if ((millis() - timeOfLastTx) > HEARTBEAT_INTERVAL) {
    Serial.println("Heartbeat!");
    sendState();
    timeOfLastTx = millis();
  }
  

  on_btn.tick();
  off_btn.tick();

  wdt_reset();

  delay(10);
}
