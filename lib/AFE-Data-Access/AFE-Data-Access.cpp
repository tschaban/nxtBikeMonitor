/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Data-Access.h"

AFEDataAccess::AFEDataAccess() {}

boolean AFEDataAccess::isFirstTimeLaunch() {
  AFEEEPROM Eeprom;
  return Eeprom.read(0);
}

void AFEDataAccess::deviceConfigured() {
  AFEEEPROM Eeprom;
  Eeprom.write(0, true);
}

DEVICE AFEDataAccess::getDeviceConfiguration() {
  DEVICE configuration;
  configuration.isLED[0] = true;
  configuration.isLED[1] = false;
  configuration.isSwitch[0] = true;
  configuration.isSwitch[1] = false;
  configuration.isRelay[0] = false;
  configuration.isDS18B20 = false;
  configuration.isNTK10K = true;
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
  configuration.gpio = 2;
  configuration.changeToOppositeValue = false;
  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, LED configuration) {}

uint8_t AFEDataAccess::getSystemLedID() { return 0; }
void AFEDataAccess::saveSystemLedID(uint8_t id) {}

RELAY AFEDataAccess::getRelayConfiguration(uint8_t id) {
  RELAY configuration;
  configuration.gpio = 12;
  configuration.ledID = 0;
  return configuration;
}

void AFEDataAccess::saveConfiguration(uint8_t id, RELAY configuration) {}

SWITCH AFEDataAccess::getSwitchConfiguration(uint8_t id) {
  SWITCH configuration;
  configuration.gpio = 0;
  configuration.sensitiveness = 50;
  configuration.functionality = SWITCH_MULTI;
  return configuration;
}

void AFEDataAccess::saveConfiguration(uint8_t id, SWITCH configuration) {}

DS18B20 AFEDataAccess::getSensorConfiguration() {
  DS18B20 configuration;
  configuration.gpio = 14;
  configuration.interval = 60;
  return configuration;
}
void AFEDataAccess::saveConfiguration(DS18B20 configuration) {}

boolean AFEDataAccess::getRelayState(uint8_t id) { return true; }
void AFEDataAccess::saveRelayState(uint8_t id, boolean state) {}

uint8_t AFEDataAccess::getDeviceMode() { return 0; }
void AFEDataAccess::saveDeviceMode(uint8_t mode) {}

NTK10K AFEDataAccess::getNTK10KSensorConfiguration() {
  NTK10K configuration;
  configuration.interval = 10;
  configuration.numberOfSampling = 20;
  configuration.VCC = 3.3;
  configuration.Rs = 150000;
  return configuration;
}
void AFEDataAccess::saveNTK10KSensorConfiguration(NTK10K configuration) {}
