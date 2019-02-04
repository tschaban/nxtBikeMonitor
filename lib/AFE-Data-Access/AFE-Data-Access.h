/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Data_Access_h
#define _AFE_Data_Access_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Configuration.h>
#include <AFE-Data-Structures.h>
#include <ArduinoJson.h>
#include <FS.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class AFEDataAccess {
private:
public:
  AFEDataAccess();

  DEVICE getDeviceConfiguration();
  void saveConfiguration(DEVICE configuration);

  NETWORK getNetworkConfiguration();
  void saveConfiguration(NETWORK configuration);

  RELAY getRelayConfiguration(uint8_t id);
  void saveConfiguration(uint8_t id, RELAY configuration);

  boolean getRelayState(uint8_t id);
  void saveRelayState(uint8_t id, boolean state);

  SWITCH getSwitchConfiguration(uint8_t id);
  void saveConfiguration(uint8_t id, SWITCH configuration);

  uint8_t getDeviceMode();
  void saveDeviceMode(uint8_t mode);

  LED getLEDConfiguration(uint8_t id);
  void saveConfiguration(uint8_t id, LED configuration);

  uint8_t getSystemLedID();
  void saveSystemLedID(uint8_t id);

  DS18B20 getSensorConfiguration();
  void saveConfiguration(DS18B20 configuration);
};
#endif
