/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Sensor-NTK10K.h"

AFESensorNTK10K::AFESensorNTK10K(){};

void AFESensorNTK10K::begin() {
  AFEDataAccess Data;
  configuration = Data.getNTK10KSensorConfiguration();
  _initialized = true;
}

float AFESensorNTK10K::getTemperature() { return temperature; }

boolean AFESensorNTK10K::isReady() {
  if (ready) {
    ready = false;
    return true;
  } else {
    return false;
  }
}

void AFESensorNTK10K::listener() {
  if (_initialized) {
    unsigned long time = millis();

    if (startTime == 0) {
      startTime = time;
    }

    if (time - startTime >= configuration.interval * 1000) {

      if (counterOfSamplings < configuration.numberOfSampling) {
        analogData = analogRead(A0);
      } else {
#ifdef DEBUG
        Serial << endl << endl << "-------------- Reading NTK10K -------------";
#endif

#ifdef DEBUG
        Serial << endl
               << " - Analog value = "
               << (uint16_t)analogData / configuration.numberOfSampling;
#endif

        temperature = calculateTemperature((uint16_t)analogData /
                                           configuration.numberOfSampling);

#ifdef DEBUG
        Serial << endl << " - Temperature = " << temperature << " C";
        Serial << endl
               << " - Sampling time = "
               << millis() - startTime - configuration.interval * 1000
               << "msec";
#endif

        counterOfSamplings = 0;
        ready = true;
        startTime = 0;

#ifdef DEBUG
        Serial << endl << "-------------------------------------------";
#endif
      }
    }
  }
}

float AFESensorNTK10K::calculateTemperature(uint16_t analogData) {
  double V_NTC = (double)analogData / 1024;
  double R_NTC = (configuration.Rs * V_NTC) / (configuration.VCC - V_NTC);
  R_NTC = log(R_NTC);
  return (1 / (0.001129148 +
               (0.000234125 + (0.0000000876741 * R_NTC * R_NTC)) * R_NTC)) -
         273.15;
}
