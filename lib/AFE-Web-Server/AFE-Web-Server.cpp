/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Web-Server.h"

AFEWebServer::AFEWebServer() {}

void AFEWebServer::begin() {
  httpUpdater.setup(&server);
  server.begin();
}

void AFEWebServer::listener() { server.handleClient(); }

boolean AFEWebServer::httpAPIlistener() { return receivedHTTPCommand; }

void AFEWebServer::publishHTML(String page) {
  uint16_t pageSize = page.length();
  uint16_t size = 1024;
  server.setContentLength(pageSize);
  if (pageSize > size) {
    server.send(200, "text/html", page.substring(0, size));
    uint16_t transfered = size;
    uint16_t nextChunk;
    while (transfered < pageSize) {
      nextChunk = transfered + size < pageSize ? transfered + size : pageSize;
      server.sendContent(page.substring(transfered, nextChunk));
      transfered = nextChunk;
    }
  } else {
    server.send(200, "text/html", page);
  }
}

void AFEWebServer::sendJSON(String json) {
  server.send(200, "application/json", json);
}

void AFEWebServer::handle(const char *uri,
                          ESP8266WebServer::THandlerFunction handler) {
  server.on(uri, handler);
}

HTTPCOMMAND AFEWebServer::getHTTPCommand() {
  receivedHTTPCommand = false;
  return httpCommand;
}

void AFEWebServer::generate() {
  /* @TODO this method is not writen well */

  if (_refreshConfiguration) {
    _refreshConfiguration = false;
    Device.begin();
  }

  const String optionName = getOptionName();
  uint8_t command = getCommand();

  if (optionName == "device") {
    DEVICE data;
    if (command == SERVER_CMD_SAVE) {
      data = getDeviceData();
    }
    publishHTML(ConfigurationPanel.getDeviceConfigurationSite(command, data));
  } else if (optionName == "network") {
    NETWORK data;
    if (command == SERVER_CMD_SAVE) {
      data = getNetworkData();
    }
    publishHTML(ConfigurationPanel.getNetworkConfigurationSite(command, data));
  } else if (optionName == "led") {
    LED data[sizeof(Device.configuration.isLED)] = {};
    uint8_t dataLedID;
    if (command == SERVER_CMD_SAVE) {
      for (uint8_t i = 0; i < sizeof(Device.configuration.isLED); i++) {
        data[i] = getLEDData(i);
      }
      dataLedID = getSystemLEDData();
    }
    publishHTML(
        ConfigurationPanel.getLEDConfigurationSite(command, data, dataLedID));
  } else if (optionName == "exit") {
    publishHTML(ConfigurationPanel.getSite(optionName, command, true));
    Device.reboot(MODE_NORMAL);
  } else if (optionName == "reset") {
    publishHTML(ConfigurationPanel.getSite(optionName, command, false));
    if (command == 1) {
      Device.setDevice();
      server.client().stop();
      Device.reboot(MODE_ACCESS_POINT);
    }
  } else if (optionName == "help") {
    publishHTML(ConfigurationPanel.getSite(
        optionName, command, command == SERVER_CMD_NONE ? false : true));
    if (command == 1) {
      server.client().stop();
      Device.reboot(MODE_CONFIGURATION);
    } else if (command == 2) {
      server.client().stop();
      Device.reboot(MODE_ACCESS_POINT);
    }
  } else if (optionName == "ds18b20") {
    DS18B20 data = {};
    if (command == SERVER_CMD_SAVE) {
      data = getDS18B20Data();
    }
    publishHTML(ConfigurationPanel.getDS18B20ConfigurationSite(command, data));
  } else {
    for (uint8_t i = 0; i < sizeof(Device.configuration.isRelay); i++) {
      if (Device.configuration.isRelay[i]) {
        if (optionName == "relay" + String(i)) {
          RELAY data = {};
          if (command == SERVER_CMD_SAVE) {
            data = getRelayData(i);
          }
          publishHTML(
              ConfigurationPanel.getRelayConfigurationSite(command, data, i));
        }
      } else {
        break;
      }
    }

    for (uint8_t i = 0; i < sizeof(Device.configuration.isSwitch); i++) {
      if (Device.configuration.isSwitch[i]) {
        if (optionName == "switch" + String(i)) {
          SWITCH data = {};
          if (command == SERVER_CMD_SAVE) {
            data = getSwitchData(i);
          }
          publishHTML(
              ConfigurationPanel.getSwitchConfigurationSite(command, data, i));
        }
      } else {
        break;
      }
    }
  }
}

String AFEWebServer::getOptionName() {

  if (Device.getMode() == MODE_NORMAL) {
    /* Recived HTTP API Command */
    if (server.hasArg("command")) {
      /* Constructing command */
      server.arg("command").toCharArray(httpCommand.command,
                                        sizeof(httpCommand.command));
      if (server.arg("device")) {
        server.arg("device").toCharArray(httpCommand.device,
                                         sizeof(httpCommand.device));
      } else {
        memset(httpCommand.device, 0, sizeof httpCommand.device);
      }
      if (server.arg("name")) {
        server.arg("name").toCharArray(httpCommand.name,
                                       sizeof(httpCommand.name));
      } else {
        memset(httpCommand.name, 0, sizeof httpCommand.name);
      }

      if (server.arg("source")) {
        server.arg("source").toCharArray(httpCommand.source,
                                         sizeof(httpCommand.source));
      } else {
        memset(httpCommand.source, 0, sizeof httpCommand.source);
      }
      receivedHTTPCommand = true;
      return server.arg("command");

    } else {
      return "help";
    }
  } else {
    if (server.hasArg("option")) {
      return server.arg("option");
    } else {
      return "device";
    }
  }
}

uint8_t AFEWebServer::getCommand() {
  if (server.hasArg("cmd")) {
    return server.arg("cmd").toInt();
  } else {
    return SERVER_CMD_NONE;
  }
}

DEVICE AFEWebServer::getDeviceData() {
  DEVICE data;
  _refreshConfiguration =
      true; // it will cause that device configuration will be refeshed

  for (uint8_t i = 0; i < sizeof(Device.configuration.isLED); i++) {
    server.arg("hl").toInt() > i ? data.isLED[i] = true : data.isLED[i] = false;
  }

  for (uint8_t i = 0; i < sizeof(Device.configuration.isSwitch); i++) {
    server.arg("hs").toInt() > i ? data.isSwitch[i] = true
                                 : data.isSwitch[i] = false;
  }
  server.arg("ds").length() > 0 ? data.isDS18B20 = true
                                : data.isDS18B20 = false;

  return data;
}

NETWORK AFEWebServer::getNetworkData() {
  NETWORK data;
  if (server.arg("s").length() > 0) {
    server.arg("s").toCharArray(data.ssid, sizeof(data.ssid) + 1);
  } else {
    data.ssid[0] = '\0';
  }

  if (server.arg("p").length() > 0) {
    server.arg("p").toCharArray(data.password, sizeof(data.password) + 1);
  } else {
    data.password[0] = '\0';
  }

  if (server.arg("na").length() > 0) {
    data.noConnectionAttempts = server.arg("na").toInt();
  }
  if (server.arg("wc").length() > 0) {
    data.waitTimeConnections = server.arg("wc").toInt();
  }
  if (server.arg("ws").length() > 0) {
    data.waitTimeSeries = server.arg("ws").toInt();
  }

  return data;
}

RELAY AFEWebServer::getRelayData(uint8_t id) {
  RELAY data;

  if (server.arg("g" + String(id)).length() > 0) {
    data.gpio = server.arg("g" + String(id)).toInt();
  }

  if (server.arg("l" + String(id)).length() > 0) {
    data.ledID = server.arg("l" + String(id)).toInt();
  }

  return data;
}

SWITCH AFEWebServer::getSwitchData(uint8_t id) {
  SWITCH data;

  if (server.arg("s" + String(id)).length() > 0) {
    data.sensitiveness = server.arg("s" + String(id)).toInt();
  }

  if (server.arg("f" + String(id)).length() > 0) {
    data.functionality = server.arg("f" + String(id)).toInt();
  }

  if (server.arg("g" + String(id)).length() > 0) {
    data.gpio = server.arg("g" + String(id)).toInt();
  }

  return data;
}

LED AFEWebServer::getLEDData(uint8_t id) {
  LED data;
  if (server.arg("g" + String(id)).length() > 0) {
    data.gpio = server.arg("g" + String(id)).toInt();
  }

  server.arg("o" + String(id)).length() > 0
      ? data.changeToOppositeValue = true
      : data.changeToOppositeValue = false;

  return data;
}

uint8_t AFEWebServer::getSystemLEDData() {
  uint8_t data;

  if (server.arg("i").length() > 0) {
    data = server.arg("i").toInt();
  }

  return data;
}

DS18B20 AFEWebServer::getDS18B20Data() {
  DS18B20 data;

  if (server.arg("g").length() > 0) {
    data.gpio = server.arg("g").toInt();
  }

  if (server.arg("i").length() > 0) {
    data.interval = server.arg("i").toInt();
  }

  return data;
}
