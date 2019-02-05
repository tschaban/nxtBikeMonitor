/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Sensor_NTC10K_h
#define _AFE_Sensor_NTC10K_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Data-Access.h>

class AFESensorNTC10K {

private:
  NTC10K configuration;
  boolean ready = false;
  unsigned long startTime = 0;
  boolean _initialized = false;
  uint16_t analogData;
  uint8_t counterOfSamplings = 0;
  float temperature;
  float VCC;

  float calculateTemperature(uint16_t analogData);

public:
  AFESensorNTC10K();

  void begin();

  float getTemperature();

  boolean isReady();

  void listener();
};

#endif
