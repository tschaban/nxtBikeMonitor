/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Device.h"

AFEDevice::AFEDevice() {}

void AFEDevice::reboot(uint8_t mode) {
  AFEDataAccess Data;
  Data.saveDeviceMode(mode);
  delay(1000);
  ESP.restart();
}
