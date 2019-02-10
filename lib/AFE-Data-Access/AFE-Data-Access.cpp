/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Data-Access.h"

AFEDataAccess::AFEDataAccess() {}

boolean AFEDataAccess::isFirstTimeLaunch() {
  boolean _ret = false;
  File exists = SPIFFS.open("/device.json", "r");
  if (exists) {
    exists.close();
  } else {
    _ret = true;
  }
  return _ret;
}

uint8_t AFEDataAccess::getDeviceMode() {

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: device-mode.json : ";
#endif

  uint8_t mode = MODE_ACCESS_POINT;
  File configFile = SPIFFS.open("/device-mode.json", "r");

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
      mode = json["mode"];

#ifdef DEBUG
      Serial << "success";
      Serial << endl << "- Mode : " << mode;
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

  return mode;
}
void AFEDataAccess::saveDeviceMode(uint8_t mode) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: device-mode.json : ";
#endif

  File configFile = SPIFFS.open("/device-mode.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();
    json["mode"] = mode;
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
  Serial << endl << "--------------------------------------------------";
#endif
}

DEVICE AFEDataAccess::getDeviceConfiguration() {
  DEVICE configuration;
  configuration.isLED[0] = true;
  configuration.isLED[1] = false;
  configuration.isSwitch[0] = false;
  configuration.isSwitch[1] = false;
  configuration.isRelay[0] = false;
  configuration.isDS18B20[0] = true;
  configuration.isNTC10K = true;
  configuration.VCC = 3.3;
  return configuration;
}
void AFEDataAccess::saveConfiguration(DEVICE configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: device.json : ";
#endif

  File configFile = SPIFFS.open("/device.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();
    json["isLED"][0] = configuration.isLED[0];
    json["isLED"][1] = configuration.isLED[1];
    json["isSwitch"][0] = configuration.isSwitch[0];
    json["isSwitch"][1] = configuration.isSwitch[1];
    json["isRelay"] = configuration.isRelay[0];
    json["isDS18B20"][0] = configuration.isDS18B20;
    json["isNTC10K"] = configuration.isNTC10K;
    json["VCC"] = configuration.VCC;
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
  Serial << endl << "--------------------------------------------------";
#endif
}

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

      sprintf(configuration.ssid, json["ssid"]);
      sprintf(configuration.password, json["password"]);
      configuration.noConnectionAttempts = json["noConnectionAttempts"];
      configuration.waitTimeConnections = json["waitTimeConnections"];
      configuration.waitTimeSeries = json["waitTimeSeries"];

#ifdef DEBUG
      Serial << "success";
      Serial << endl
             << "- WiFi : " << configuration.ssid << ":"
             << configuration.password;
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
  Serial << endl << "--------------------------------------------------";
#endif
}

LED AFEDataAccess::getLEDConfiguration(uint8_t id) {
  LED configuration;
  configuration.gpio = 2;
  configuration.changeToOppositeValue = false;
  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, LED configuration) {}

uint8_t AFEDataAccess::getSystemLedID() { return 1; }
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
  configuration.interval = 5;
  return configuration;
}
void AFEDataAccess::saveConfiguration(DS18B20 configuration) {}

boolean AFEDataAccess::getRelayState(uint8_t id) { return true; }
void AFEDataAccess::saveRelayState(uint8_t id, boolean state) {}

NTC10K AFEDataAccess::getNTC10KSensorConfiguration() {
  NTC10K configuration;
  configuration.interval = 5;
  configuration.numberOfSamples = 20;
  configuration.correction = 0;
  configuration.hardware.balancingResistor = 10000;
  configuration.hardware.ADCResolution = 1024;
  configuration.hardware.VCC = 3.295;

  return configuration;
}
void AFEDataAccess::saveNTC10KSensorConfiguration(NTC10K configuration) {}
