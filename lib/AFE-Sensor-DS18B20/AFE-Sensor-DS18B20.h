/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Sensor_DS18B20_h
#define _AFE_Sensor_DS18B20_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Data-Access.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class AFESensorDS18B20 {

private:
  DS18B20 configuration;

  boolean ready = false;
  unsigned long startTime = 0;
  boolean _initialized = false;
  DeviceAddress address[MAX_DS18B20_SENSORS];
  float currentTemperature[MAX_DS18B20_SENSORS];
  uint8_t numberOfSensors = 0;

#ifdef DEBUG
  String addressToString(DeviceAddress address);
#endif

public:
  /* Constructor: entry parameter is GPIO number where Sensor is connected to */
  AFESensorDS18B20();

  void begin();

  float getTemperature(uint8_t sensorNumber = 0);

  boolean isReady();

  /* Method has to be added to the loop in order to listen for sensor value
   * changes */
  void listener();
};

#endif
