/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_DS18B20_Structure_h
#define _AFE_DS18B20_Structure_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_DS18B20_SENSORS 4

struct DS18B20_DETAILS {
  uint8_t id;
  uint8_t function; // location of the sensor
};

struct DS18B20 {
  uint8_t gpio;
  uint8_t interval;
  DS18B20_DETAILS sesnor[MAX_DS18B20_SENSORS];
};

#endif
