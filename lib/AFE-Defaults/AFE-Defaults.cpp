/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Defaults.h"

AFEDefaults::AFEDefaults() {}

void AFEDefaults::set() {

  Serial << endl << endl << "------------- Setting the device --------------";

#ifdef DEBUG
  Serial << endl << "Saving default configuration" << endl << " - device: ";
#endif

  DEVICE deviceConfiguration;
  Data->saveConfiguration(deviceConfiguration);

#ifdef DEBUG
  Serial << "completed" << endl << " - network: ";
#endif

  /* Network default config */
  NETWORK networkConfiguration;
  networkConfiguration.ssid[0] = '\0';
  networkConfiguration.password[0] = '\0';
  networkConfiguration.noConnectionAttempts = 10;
  networkConfiguration.waitTimeConnections = 1;
  networkConfiguration.waitTimeSeries = 60;
  Data->saveConfiguration(networkConfiguration);

#ifdef DEBUG
  Serial << endl << " - relay: ";
#endif

  deviceConfiguration;
  Data->saveConfiguration(deviceConfiguration);

#ifdef DEBUG
  Serial << endl << " - LED: ";
#endif

#ifdef DEBUG
  Serial << "completed" << endl << " - switch: ";
#endif

#ifdef DEBUG
  Serial << "completed" << endl << " - sensor DS18B20: ";
#endif

#ifdef DEBUG
  Serial << endl << "-----------------------------------------------";
#endif
}
