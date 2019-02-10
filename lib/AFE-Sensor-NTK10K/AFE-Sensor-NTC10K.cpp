/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Sensor-NTC10K.h"

AFESensorNTC10K::AFESensorNTC10K(){};

void AFESensorNTC10K::begin() {
  AFEDataAccess Data;
  configuration = Data.getNTC10KSensorConfiguration();

  DEVICE device = Data.getDeviceConfiguration();

  _initialized = true;
}

double AFESensorNTC10K::getTemperature() { return temperature; }

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

      if (counterOfSamplings < configuration.numberOfSamples) {
        analogData += analogRead(A0);
        counterOfSamplings++;
      } else {

#ifdef DEBUG
        Serial << endl
               << " - Number of samples: " << counterOfSamplings << endl
               << " - Analog value = "
               << analogData / configuration.numberOfSamples;
#endif

        temperature =
            calculateTemperature(analogData / configuration.numberOfSamples) +
            configuration.correction;

#ifdef DEBUG
        Serial << endl
               << " - Temperature correction: " << configuration.correction
               << endl
               << " - Temperature = " << temperature << " C";
        Serial << endl
               << " - Sampling time = "
               << millis() - startTime - configuration.interval * 1000
               << "msec";
#endif

        counterOfSamplings = 0;
        analogData = 0;
        ready = true;
        startTime = 0;

#ifdef DEBUG
        Serial << endl << "-------------------------------------------";
#endif
      }
    }
  }
}

double AFESensorNTC10K::calculateTemperature(uint16_t analogData) {

  const double A = 0.001129148;
  const double B = 0.000234125;
  const double C = 0.0000000876741;

  double V_NTC = (analogData * configuration.hardware.VCC) /
                 configuration.hardware.ADCResolution;
  double R_NTC = (configuration.hardware.VCC *
                  configuration.hardware.balancingResistor / V_NTC) -
                 configuration.hardware.balancingResistor;

#ifdef DEBUG
  Serial << endl
         << " - VCC=" << configuration.hardware.VCC << endl
         << " - ADC Resolution=" << configuration.hardware.ADCResolution << endl
         << " - Balancing Resistor=" << configuration.hardware.balancingResistor
         << endl
         << " - V[NTC]=" << V_NTC << endl
         << " - R[NTC]=" << R_NTC;
#endif

  return (1 / (A + (B * log(R_NTC)) + (C * pow((log(R_NTC)), 3)))) - 273.15;
}
