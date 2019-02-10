/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_DEVICE_Structure_h
#define _AFE_DEVICE_Structure_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define MODE_NORMAL 0
#define MODE_CONFIGURATION 1
#define MODE_ACCESS_POINT 2

#define DEVICE_NO_OF_LEDS 2
#define DEVICE_NO_OF_SWITCHES 2
#define DEVICE_NO_OF_RELAYS 1
#define DEVICE_NO_OF_DS18B20 4

/* Custom DEVICE structure definition */
struct DEVICE {
  boolean isLED[DEVICE_NO_OF_LEDS];
  boolean isSwitch[DEVICE_NO_OF_SWITCHES];
  boolean isRelay[DEVICE_NO_OF_RELAYS];
  boolean isDS18B20[DEVICE_NO_OF_DS18B20];
  boolean isNTC10K;
  double VCC;
};

#endif
