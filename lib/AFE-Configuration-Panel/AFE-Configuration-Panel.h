/* AFE Firmware for smart home devices
 LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Configuration_Panel_h
#define _AFE_Configuration_Panel_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Data-Access.h>
#include <AFE-Device.h>
#include <AFE-Sites-Generator.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class AFEConfigurationPanel {

private:
  AFESitesGenerator Site;
  AFEDataAccess Data;
  AFEDevice Device;
  uint8_t language;
  uint16_t siteBufferSize = 7500;

public:
  /* Constructor */
  AFEConfigurationPanel();

  /* It returns configuration site */
  String getSite(const String option, uint8_t command, boolean data);
  String getDeviceConfigurationSite(uint8_t command, DEVICE data);
  String getNetworkConfigurationSite(uint8_t command, NETWORK data);

  String getLEDConfigurationSite(uint8_t command, LED data, uint8_t ledIndex);

  String getRelayConfigurationSite(uint8_t command, RELAY data,
                                   uint8_t relayIndex);

  String getSwitchConfigurationSite(uint8_t command, SWITCH data,
                                    uint8_t relayIndex);

  String getDS18B20ConfigurationSite(uint8_t command, DS18B20 data);

  /* It generates site for firmware upgrade */
  String firmwareUpgradeSite();

  /* It generates sites post firmware upgrade */
  String postFirmwareUpgradeSite(boolean status);
};
#endif
