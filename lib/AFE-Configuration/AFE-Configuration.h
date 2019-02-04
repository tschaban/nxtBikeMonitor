/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Configuration_h
#define _AFE_Configuration_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define FIRMWARE_VERSION "0.0.1"

#define SERVER_CMD_SAVE 1
#define SERVER_CMD_NONE 0

#ifdef DEBUG
#define DEBUG_INTERVAL 10
#endif

#endif
