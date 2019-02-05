/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Sensor-NTC10K.h"

AFESensorNTC10K::AFESensorNTC10K(){};

void AFESensorNTC10K::begin() {
  AFEDataAccess Data;
  configuration = Data.getNTC10KSensorConfiguration();

  DEVICE device = Data.getDeviceConfiguration();
  VCC = device.VCC;

  _initialized = true;
}

float AFESensorNTC10K::getTemperature() { return temperature; }

boolean AFESensorNTC10K::isReady() {
  if (ready) {
    ready = false;
    return true;
  } else {
    return false;
  }
}

void AFESensorNTC10K::listener() {
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
        Serial << endl << endl << "-------------- Reading NTC10K -------------";
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

float AFESensorNTC10K::calculateTemperature(uint16_t analogData) {
  double V_NTC = (double)analogData / 1024;
  double R_NTC = (configuration.balancingResistor * V_NTC) / (VCC - V_NTC);

#ifdef DEBUG
  Serial << endl << "V[NTC]=" << V_NTC << ", R[NTC]=" << R_NTC << ", ";
#endif

  R_NTC = log(R_NTC);

#ifdef DEBUG
  Serial << "R[NTC-ln]=" << R_NTC;
#endif

  return (1 / (0.001129148 +
               (0.000234125 + (0.0000000876741 * R_NTC * R_NTC)) * R_NTC)) -
         273.15;
}
