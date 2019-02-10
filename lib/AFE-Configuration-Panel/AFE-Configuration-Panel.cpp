#include "AFE-Configuration-Panel.h"

AFEConfigurationPanel::AFEConfigurationPanel() {}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      boolean redirect) {

  String page;
  redirect ? page = Site.generateHeader(10) : page = Site.generateHeader(0);

  if (option == "upgrade") {
    page += Site.addUpgradeSection();
  } else if (option == "reset") {
    page += Site.addResetSection(command);
  } else if (option == "exit") {
    page += Site.addExitSection();
  } else if (option == "help") {
    if (command == 0) {
      page += Site.addHelpSection();
    } else if (command == 1 || command == 2) {
      page += Site.addExitSection();
    }
  } else {
    page += "<h1>Page Not Found</h1>";
  }

  page += Site.generateFooter();
  delay(10);
  return page;
}

String AFEConfigurationPanel::getDeviceConfigurationSite(uint8_t command,
                                                         DEVICE data) {

  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(data);
  }
  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form action=\"/?option=device&cmd=1\"  method=\"post\">";
  page += Site.addDeviceConfiguration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getNetworkConfigurationSite(uint8_t command,
                                                          NETWORK data) {

  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(data);
  }
  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form action=\"/?option=network&cmd=1\"  method=\"post\">";
  page += Site.addNetworkConfiguration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getLEDConfigurationSite(uint8_t command, LED data,
                                                      uint8_t ledIndex) {

  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(ledIndex, data);
  }

  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form action=\"/?option=led";
  page += ledIndex;
  page += "&cmd=1\"  method=\"post\">";
  page += Site.addLEDConfiguration(ledIndex);
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getRelayConfigurationSite(uint8_t command,
                                                        RELAY data,
                                                        uint8_t relayIndex) {
  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(relayIndex, data);
  }

  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form action=\"/?option=relay";
  page += relayIndex;
  page += "&cmd=1\"  method=\"post\">";
  page += Site.addRelayConfiguration(relayIndex);
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getSwitchConfigurationSite(uint8_t command,
                                                         SWITCH data,
                                                         uint8_t switchIndex) {

  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(switchIndex, data);
  }

  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form action=\"/?option=switch";
  page += switchIndex;
  page += "&cmd=1\"  method=\"post\">";
  page += Site.addSwitchConfiguration(switchIndex);
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

/* DS18B20 and DHxx Sensors */
String AFEConfigurationPanel::getDS18B20ConfigurationSite(uint8_t command,
                                                          DS18B20 data)

{
  if (command == SERVER_CMD_SAVE) {
    Data.saveConfiguration(data);
  }

  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();

  page += "<form action=\"/?option=ds18b20&cmd=1\"  method=\"post\">";
  page += Site.addDS18B20Configuration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"";
  page += "Zapisz";
  page += "\"></form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::firmwareUpgradeSite() {
  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader();
  page += "<form method=\"post\" action=\"\" "
          "enctype=\"multipart/form-data\">";
  page += Site.addUpgradeSection();
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::postFirmwareUpgradeSite(boolean status) {
  String page;
  page.reserve(siteBufferSize);
  page = Site.generateHeader(15);
  page += Site.addPostUpgradeSection(status);
  page += Site.generateFooter();
  return page;
}
