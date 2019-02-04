/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Device.h"

AFEDevice::AFEDevice() {}

void AFEDevice::begin() {
  deviceMode = Data.getDeviceMode();
  configuration = Data.getDeviceConfiguration();
}

void AFEDevice::reboot(uint8_t mode) {
  saveMode(mode);
  delay(1000);
  ESP.restart();
}

uint8_t AFEDevice::getMode() { return deviceMode; }

void AFEDevice::saveMode(uint8_t mode) { Data.saveDeviceMode(mode); }

boolean AFEDevice::isFirstTimeLaunch() { return Data.isFirstTimeLaunch(); }

void AFEDevice::setDevice() {
  AFEDefaults Defaults;
  Defaults.eraseConfiguration();
  Defaults.set();
}

boolean AFEDevice::isConfigured() {
  NETWORK configuration = Data.getNetworkConfiguration();
  if (strlen(configuration.ssid) == 0 || strlen(configuration.password) == 0) {
    return false;
  } else {
    return true;
  }
}
