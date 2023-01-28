#include <Arduino.h>
#include <LoRa.h>
#include <OneButton.h>

#include <enums.h>
#include <settings.h>


mode currentMode = ROVER_ON;
long timeOfLastTx = 0;        // in ms

OneButton on_btn(ON_SW_PIN, true);
OneButton off_btn(OFF_SW_PIN, true);


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
}
void on_btn_click() {
  Serial.println("ROVER ON");
  currentMode = ROVER_ON;
  sendState();

  digitalWrite(ON_LED_PIN, HIGH);  // turn on "ON" LED
  digitalWrite(OFF_LED_PIN, LOW);
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello world!");

  // set up LoRa
  LoRa.setSPIFrequency(500000);
  bool status = LoRa.begin(433E6);          // 433 MHz
  LoRa.setTxPower(TX_POWER);

  if (!status) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Serial.println("Starting LoRa worked!!");

  // while (!LoRa.available()) {
  //   Serial.println("Waiting for LoRa");
  //   delay(100);
  // }
  
  Serial.println("LoRa OK!");

  // set up pins
  // pinMode(ON_SW_PIN, INPUT_PULLUP);
  // pinMode(OFF_SW_PIN, INPUT_PULLUP);
  pinMode(ON_LED_PIN, OUTPUT);
  pinMode(OFF_LED_PIN, OUTPUT);

  on_btn.attachClick(on_btn_click);
  off_btn.attachClick(off_btn_click);

  digitalWrite(ON_LED_PIN, HIGH);   // turn on "ON" LED
  digitalWrite(OFF_LED_PIN, LOW);
}

void loop() {
  Serial.println("LOOPING");

  // Read switches
  // if (!digitalRead(OFF_SW_PIN)) {
  //   Serial.println("ROVER OFF");
  //   currentMode = ROVER_OFF;
  //   sendState();

  //   digitalWrite(OFF_LED_PIN, HIGH);  // turn on "OFF" LED
  //   digitalWrite(ON_LED_PIN, LOW);
  // }
  // else if (!digitalRead(ON_SW_PIN)) {
  //   Serial.println("ROVER ON");
  //   currentMode = ROVER_ON;
  //   sendState();

  //   digitalWrite(ON_LED_PIN, HIGH);  // turn on "ON" LED
  //   digitalWrite(OFF_LED_PIN, LOW);
  // }

  // Send state if time is up
  if ((millis() - timeOfLastTx) > HEARTBEAT_INTERVAL) {
    Serial.println("Heartbeat!");
    sendState();
    timeOfLastTx = millis();
  }

  on_btn.tick();
  off_btn.tick();

  delay(10);
}
