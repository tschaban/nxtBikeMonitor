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
  double analogData = 0;
  uint8_t counterOfSamplings = 0;
  double temperature;

  double calculateTemperature(uint16_t analogData);

public:
  AFESensorNTC10K();

  void begin();

  double getTemperature();

  boolean isReady();

  void listener();
};

#endif
