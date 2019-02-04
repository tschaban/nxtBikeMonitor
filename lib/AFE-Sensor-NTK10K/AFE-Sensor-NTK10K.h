/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Sensor_NTK10K_h
#define _AFE_Sensor_NTK10K_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Data-Access.h>

class AFESensorNTK10K {

private:
  NTK10K configuration;
  boolean ready = false;
  unsigned long startTime = 0;
  boolean _initialized = false;
  uint16_t analogData;
  uint8_t counterOfSamplings = 0;
  float temperature;

  float calculateTemperature(uint16_t analogData);

public:
  AFESensorNTK10K();

  void begin();

  float getTemperature();

  boolean isReady();

  void listener();
};

#endif
