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

/* Custom DEVICE structure definition */
struct DEVICE {
  boolean isLED[2];
  boolean isSwitch[2];
  boolean isRelay[1];
  boolean isDS18B20;
  boolean isNTK10K;
};

#endif
