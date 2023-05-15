#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>


#define TX_POWER 20                 // <= 20

#define SW_PIN 4                 // digital pins!
#define ON_LED_PIN 2
#define OFF_LED_PIN 3

#define HEARTBEAT_INTERVAL 10000    // in ms


#define ROVER_ON_MAGIC "3141592653 ON"      // must be same on TX and RX
#define ROVER_OFF_MAGIC "3141592653 OFF"


#endif  // SETTINGS_H
