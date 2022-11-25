#include <Arduino.h>
#include <LoRa.h>

#include <enums.h>
#include <settings.h>


mode currentMode = ROVER_ON;
long timeOfLastTx = 0;        // in ms


int sendState() {
  LoRa.beginPacket();

  if (currentMode == ROVER_OFF) {
    LoRa.print(ROVER_OFF_MAGIC);
  }
  else if (currentMode == ROVER_ON) {
    LoRa.print(ROVER_ON_MAGIC);
  }

  return LoRa.endPacket();
}


void setup() {
  // set up LoRa
  LoRa.begin(433E6);          // 433 MHz
  LoRa.setTxPower(TX_POWER);

  // set up pins
  pinMode(ON_SW_PIN, INPUT_PULLUP);
  pinMode(OFF_SW_PIN, INPUT_PULLUP);
  pinMode(ON_LED_PIN, OUTPUT);
  pinMode(OFF_LED_PIN, OUTPUT);
}

void loop() {
  // Read switches
  if (!digitalRead(OFF_SW_PIN)) {
    currentMode = ROVER_OFF;
    sendState();

    digitalWrite(OFF_LED_PIN, HIGH);  // turn on "OFF" LED
    digitalWrite(ON_LED_PIN, LOW);
  }
  else if (!digitalRead(ON_SW_PIN)) {
    currentMode = ROVER_ON;
    sendState();

    digitalWrite(ON_LED_PIN, HIGH);  // turn on "ON" LED
    digitalWrite(OFF_LED_PIN, LOW);
  }

  // Send state if time is up
  if ((millis() - timeOfLastTx) > HEARTBEAT_INTERVAL) {
    sendState();
    timeOfLastTx = millis();
  }
}
