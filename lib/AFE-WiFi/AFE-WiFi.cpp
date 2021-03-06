/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Wifi.h"

AFEWiFi::AFEWiFi() {}

void AFEWiFi::begin(uint8_t mode) {

  AFEDataAccess Data;
  AFEDevice Device;

  WiFiMode = mode;

  if (WiFiMode != MODE_ACCESS_POINT) {
    networkConfiguration = Data.getNetworkConfiguration();
  }

  uint8_t systeLedID = Data.getSystemLedID();
  if (systeLedID > 0) {
    Led.begin(systeLedID - 1);
  }

  // Cleaning @TODO is it neded?
  Data = {};
  WiFi.hostname("nxtBike");
  if (mode == MODE_ACCESS_POINT) {

#ifdef DEBUG
    Serial << endl << "Starting HotSpot: ";
#endif

    IPAddress apIP(192, 168, 5, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("nxtBike");
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(53, "www.example.com", apIP);

#ifdef DEBUG
    Serial << "completed";
#endif
  } else {
#ifdef DEBUG
    Serial << endl << "Starting WiFi: in WIFI_STA mode";
#endif
    WiFi.mode(WIFI_STA);
  }
}

void AFEWiFi::listener() {
  if (WiFiMode != MODE_ACCESS_POINT) {
    if (!connected()) {
      if (sleepMode) {
        if (millis() - sleepStartTime >=
            networkConfiguration.waitTimeSeries * 1000) {
          sleepMode = false;
        }
      } else {
        if (delayStartTime == 0) {
          delayStartTime = millis();
          if (connections == 0) {

            /* Checking if WiFi is configured */
            if (strlen(networkConfiguration.ssid) == 0 ||
                strlen(networkConfiguration.password) == 0) {
#ifdef DEBUG
              Serial << endl
                     << "WiFI is not configured. Going to configuration mode";
#endif
              AFEDevice Device;
              Device.reboot(MODE_ACCESS_POINT);
            }

            WiFi.begin(networkConfiguration.ssid,
                       networkConfiguration.password);
#ifdef DEBUG
            Serial << endl << "INFO: Starting establishing WiFi connection ";
            Serial << endl
                   << networkConfiguration.ssid << " - "
                   << networkConfiguration.password;
#endif
          }
        }

        if (ledStartTime == 0) {
          ledStartTime = millis();
        }

        if (millis() > ledStartTime + 500) {
          Led.toggle();
          ledStartTime = 0;
        }

        if (millis() > delayStartTime +
                           (networkConfiguration.waitTimeConnections * 1000)) {
          connections++;

#ifdef DEBUG
          Serial << endl
                 << "INFO: WiFi connection attempt: " << connections << " from "
                 << networkConfiguration.noConnectionAttempts;
#endif
          delayStartTime = 0;
        }

        if (connections == networkConfiguration.noConnectionAttempts) {
          sleepMode = true;
          WiFi.disconnect();
          sleepStartTime = millis();
          delayStartTime = 0;

          ledStartTime = 0;
          Led.off();

          connections = 0;
#ifdef DEBUG
          Serial << endl
                 << "WARN: Not able to connect.Going to sleep mode for "
                 << networkConfiguration.waitTimeSeries << "sec.";
#endif
        }
      }
    } else {
      if (connections > 0) {
        connections = 0;
        delayStartTime = 0;

        ledStartTime = 0;
        Led.off();

#ifdef DEBUG
        Serial << endl
               << "INFO: Connection established"
               << ", MAC: " << WiFi.macAddress() << ", IP: " << WiFi.localIP();
#endif
      }
    }
  }
}

boolean AFEWiFi::connected() {

  if (WiFi.status() == WL_CONNECTED) {
    delay(1);
    if (disconnected) {
      eventConnectionEstablished = true;
      disconnected = false;
    }
    return true;
  } else {
    disconnected = true;
    return false;
  }
}

void AFEWiFi::APListener() { dnsServer.processNextRequest(); }

boolean AFEWiFi::eventConnected() {
  boolean returnValue = eventConnectionEstablished;
  eventConnectionEstablished = false;
  return returnValue;
}
