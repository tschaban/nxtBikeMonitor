/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Web_Handlers_h
#define _AFE_Web_Handlers_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/* Method handles favicon.ico request */
void handleFavicon() {}

/* Method handles all HTTP request */
void handleHTTPRequests() { WebServer.generate(); }

#endif
