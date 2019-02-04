/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Data-Access.h"

AFEDataAccess::AFEDataAccess() {}

DEVICE AFEDataAccess::getDeviceConfiguration() {
  DEVICE configuration;
  return configuration;
}
void AFEDataAccess::saveConfiguration(DEVICE configuration) {}

NETWORK AFEDataAccess::getNetworkConfiguration() {

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: network.json : ";
#endif

  NETWORK configuration;
  File configFile = SPIFFS.open("/network.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (json.success()) {

      *configuration.ssid = json["ssid"];
      *configuration.password = json["password"];
      configuration.noConnectionAttempts = json["noConnectionAttempts"];
      configuration.waitTimeConnections = json["waitTimeConnections"];
      configuration.waitTimeSeries = json["waitTimeSeries"];

#ifdef DEBUG
      Serial << "success";
#endif

    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}

void AFEDataAccess::saveConfiguration(NETWORK configuration) {

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: network.json : ";
#endif

  File configFile = SPIFFS.open("/network.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();
    json["ssid"] = configuration.ssid;
    json["password"] = configuration.password;
    json["noConnectionAttempts"] = configuration.noConnectionAttempts;
    json["waitTimeConnections"] = configuration.waitTimeConnections;
    json["waitTimeSeries"] = configuration.waitTimeSeries;
    json.printTo(configFile);
    configFile.close();

#ifdef DEBUG
    Serial << "success";
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
#endif
}

LED AFEDataAccess::getLEDConfiguration(uint8_t id) {
  LED configuration;
  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, LED configuration) {}

uint8_t AFEDataAccess::getSystemLedID() { return 0; }
void AFEDataAccess::saveSystemLedID(uint8_t id) {}

RELAY AFEDataAccess::getRelayConfiguration(uint8_t id) {
  RELAY configuration;
  return configuration;
}

void AFEDataAccess::saveConfiguration(uint8_t id, RELAY configuration) {}

SWITCH AFEDataAccess::getSwitchConfiguration(uint8_t id) {
  SWITCH configuration;
  return configuration;
}

void AFEDataAccess::saveConfiguration(uint8_t id, SWITCH configuration) {}

DS18B20 AFEDataAccess::getSensorConfiguration() {
  DS18B20 configuration;
  return configuration;
}
void AFEDataAccess::saveConfiguration(DS18B20 configuration) {}

boolean AFEDataAccess::getRelayState(uint8_t id) { return true; }
void AFEDataAccess::saveRelayState(uint8_t id, boolean state) {}

uint8_t AFEDataAccess::getDeviceMode() { return 0; }
void AFEDataAccess::saveDeviceMode(uint8_t mode) {}
