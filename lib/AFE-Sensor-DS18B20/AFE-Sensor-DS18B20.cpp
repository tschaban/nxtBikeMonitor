/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Sensor-DS18B20.h"

AFESensorDS18B20::AFESensorDS18B20(){};

void AFESensorDS18B20::begin() {
  AFEDataAccess Data;
  configuration = Data.getSensorConfiguration();

  OneWire wireProtocol(configuration.gpio);
  DallasTemperature Sensors(&wireProtocol);

  Sensors.begin();

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- DS18B20s Initializing -----------------" << endl
         << "- GPIO: " << configuration.gpio << endl
         << "- Interval: " << configuration.interval;
  Serial << endl
         << "- Parasite power is: "
         << (Sensors.isParasitePowerMode() ? "ON" : "OFF");
#endif

  numberOfSensors = Sensors.getDeviceCount();

#ifdef DEBUG
  Serial << endl << "- Number of sensors: " << numberOfSensors;
#endif

  Sensors.requestTemperatures();

#ifdef DEBUG
  Serial << endl << "- Searching for sensors:";
#endif

  for (uint8_t i = 0; i < numberOfSensors; i++) {
    // Search the wire for address
    if (Sensors.getAddress(address[i], i)) {
#ifdef DEBUG
      Serial << endl
             << "   - found: " << i + 1 << " with address "
             << addressToString(address[i]);
      Serial << ", resolution: " << Sensors.getResolution(address[i]) << "b";
#endif
      currentTemperature[i] = Sensors.getTempC(address[i]);
#ifdef DEBUG
      Serial << ", temperature: " << currentTemperature[i] << " C";
    } else {
      Serial << endl
             << "   - found ghost device at: " << i + 1
             << " but could not detect address. Check power and cabling";
#endif
    }
  }

  if (numberOfSensors > 0) {
    _initialized = true;
#ifdef DEBUG
    Serial << endl << "- DS18B20 initialized";
  } else {
    Serial << endl << "- DS18B20 NOT initialized";
#endif
  }

#ifdef DEBUG
  Serial << endl << "---------------------------------------------------------";
#endif
}

float AFESensorDS18B20::getTemperature(uint8_t sensorNumber) {
  return _initialized ? currentTemperature[sensorNumber] : -127;
}

boolean AFESensorDS18B20::isReady() {
  if (ready) {
    ready = false;
    return true;
  } else {
    return false;
  }
}

void AFESensorDS18B20::listener() {
  if (_initialized) {
    unsigned long time = millis();

    if (startTime == 0) { // starting timer. used for switch sensitiveness
      startTime = time;
    }

    if (time - startTime >= configuration.interval * 1000) {
#ifdef DEBUG
      Serial << endl
             << endl
             << "----------------- Reading DS18B20 -----------------";
      Serial << endl << "- Interval: " << (time - startTime) / 1000 << "sec.";
#endif

      OneWire wireProtocol(configuration.gpio);
      DallasTemperature Sensors(&wireProtocol);
      Sensors.begin();

      for (int i = 0; i < numberOfSensors; i++) {
        currentTemperature[i] = -127;
        do {
          currentTemperature[i] = Sensors.getTempC(address[i]);
        } while (currentTemperature[i] == 85.0 ||
                 currentTemperature[i] == (-127.0));
#ifdef DEBUG
        Serial << endl
               << "- Sensor: " << i + 1
               << ", temperature: " << currentTemperature[i] << " C";
#endif
      }

      Sensors.setWaitForConversion(false);
      Sensors.requestTemperatures();
      ready = true;
      startTime = 0;
#ifdef DEBUG
      Serial << endl << "---------------------------------------------------";
#endif
    }
  }
}

#ifdef DEBUG
String AFESensorDS18B20::addressToString(DeviceAddress address) {
  String str = "";
  for (uint8_t i = 0; i < 8; i++) {
    if (address[i] < 16)
      str += String(0, HEX);
    str += String(address[i], HEX);
  }
  return str;
}
#endif
