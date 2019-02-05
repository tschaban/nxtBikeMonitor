/*

*/

/* Includes libraries for debugging in development compilation only */
#include <AFE-Data-Access.h>
#include <AFE-Device.h>
#include <AFE-I2C-Scanner.h>
#include <AFE-LED.h>
#include <AFE-Relay.h>
#include <AFE-Sensor-DS18B20.h>
#include <AFE-Sensor-NTC10K.h>
#include <AFE-Switch.h>
#include <AFE-Web-Server.h>
#include <AFE-WiFi.h>
#include <FS.h>

#if defined(DEBUG)
#include <Streaming.h>
#endif

AFEDataAccess Data;
AFEDevice Device;
AFEWiFi Network;
AFEWebServer WebServer;
AFESwitch Switch[sizeof(Device.configuration.isSwitch)];
AFERelay Relay[sizeof(Device.configuration.isRelay)];
AFELED Led;
AFESensorDS18B20 SensorDS18B20;
AFESensorNTC10K SensorNTC10K;
AFEI2CScanner I2CScanner;

float temperature;

void setup() {

  Serial.begin(115200);
  delay(10);

/* Turn off publishing information to Serial for production compilation */
#if !defined(DEBUG)
  Serial.swap();
#endif

#ifdef DEBUG
  Serial << endl
         << endl
         << "################################ BOOTING "
            "################################";
#endif

  if (SPIFFS.begin()) {
#ifdef DEBUG
    Serial << endl << "File system mounted";
  } else {
    Serial << endl << "Failed to mount file system";
#endif
  }

  Device.begin();

#ifdef DEBUG
  Serial << endl << "All classes and global variables initialized";
#endif

  /* Checking if the device is launched for a first time. If so it loades
   * default configuration to EEPROM */
  if (Device.isFirstTimeLaunch()) {
#ifdef DEBUG
    Serial << endl << "First time launch";
#endif
    Device.setDevice();
  }

  /* Checking if WiFi is configured, if not then it runs configuration panel in
   * access point mode */
  if (Device.getMode() != MODE_ACCESS_POINT && !Device.isConfigured()) {
#ifdef DEBUG
    Serial << endl << "Going to configuration mode (HotSpot)";
#endif
    Device.reboot(MODE_ACCESS_POINT);
  }

  /* Initializing relay */
  initRelay();
#ifdef DEBUG
  Serial << endl << "Relay(s) initialized";
#endif

  /* Initialzing network */
  Network.begin(Device.getMode());
#ifdef DEBUG
  Serial << endl << "Network initialized";
#endif

  /* Initializing LED, checking if LED exists is made on Class level  */
  uint8_t systeLedID = Data.getSystemLedID();
  if (systeLedID > 0) {
    Led.begin(systeLedID - 1);
  }

  /* If device in configuration mode then it starts LED blinking */
  if (Device.getMode() == MODE_ACCESS_POINT) {
    Led.blinkingOn(100);
  }

  Network.listener();
  /* Initializing HTTP WebServer */
  WebServer.handle("/", handleHTTPRequests);
  WebServer.handle("/favicon.ico", handleFavicon);
  WebServer.begin();
#ifdef DEBUG
  Serial << endl << "WebServer initialized";
#endif

  /* Initializing switches */
  initSwitch();
#ifdef DEBUG
  Serial << endl << "Switch(es) initialized";
#endif

  if (Device.getMode() == MODE_NORMAL) {
    initSensorNTC10K();
    initSensorDS18B20();
  }

#if defined(DEBUG)
  /* Scanning I2C for devices */
  if (Device.getMode() == MODE_NORMAL) {
    I2CScanner.scanAll();
  }

  Serial << endl
         << "########################### BOOTING COMPLETED "
            "###########################"
         << endl;
#endif
}

void loop() {

  if (Device.getMode() != MODE_ACCESS_POINT) {
    if (Network.connected()) {
      if (Device.getMode() == MODE_NORMAL) {

        /* Triggerd when connectes/reconnects to WiFi */
        eventsListener();

        /* Listens for HTTP requsts. Both for configuration panel HTTP
         * requests or HTTP API requests if it's turned on */
        WebServer.listener();

        /* Relay related events */
        mainRelay();

        mainSensorNTC10K();

      } else { /* Device runs in configuration mode over WiFi */
        if (!Led.isBlinking()) {
          Led.blinkingOn(100);
        }
        WebServer.listener();
      }
    }

    else {
      if (Device.getMode() == MODE_CONFIGURATION && Led.isBlinking()) {
        Led.blinkingOff();
      }
    }
    Network.listener();
  } else { /* Deviced runs in Access Point mode */
    Network.APListener();
    WebServer.listener();
  }

  /* Listens for switch events */
  mainSwitchListener();
  mainSwitch();

  /* Led listener */
  Led.loop();

/* Debug information */
#if defined(DEBUG)
  if (Device.getMode() == MODE_NORMAL) {
    debugListener();
  }
#endif
}
