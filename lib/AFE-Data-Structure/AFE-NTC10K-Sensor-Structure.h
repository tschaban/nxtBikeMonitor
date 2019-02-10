/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_NTC10K_Structure_h
#define _AFE_NTC10K_Structure_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/* https://www.ametherm.com/thermistor/ntc-thermistors-steinhart-and-hart-equation
 */
struct NTC10K_HARDWARE_PARAMETERS {
  double balancingResistor;
  double ADCResolution;
  double VCC;
};

struct NTC10K {
  uint8_t interval;
  uint8_t numberOfSamples;
  float correction;
  NTC10K_HARDWARE_PARAMETERS hardware;
};

#endif
