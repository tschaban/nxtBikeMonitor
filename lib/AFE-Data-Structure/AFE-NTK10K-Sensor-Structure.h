/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_NTK10K_Structure_h
#define _AFE_NTK10K_Structure_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

struct NTK10K {
  uint8_t interval;
  uint8_t numberOfSampling;
  double VCC;
  uint16_t Rs;
};

#endif
