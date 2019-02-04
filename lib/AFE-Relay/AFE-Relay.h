/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Relay_h
#define _AFE_Relay_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-Data-Access.h>
#include <AFE-LED.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class AFERelay {

private:
  uint8_t _id;
  AFEDataAccess Data; // @TODO nie jest konsekwentnie jak np. w switch
  RELAY RelayConfiguration;
  AFELED Led;

public:
  /* Constructors */
  AFERelay();

  /* Method: initiates relay */
  void begin(uint8_t id);

  /* Method: Returns RELAY_OFF if relay is OFF, RELAY_ON if relay is ON */
  byte get();

  /* Turns on relay */
  void on(boolean invert = false);

  /* Turns off relay */
  void off(boolean invert = false);

  /* It returns ID of the LED that shoud indicated Relay status */
  uint8_t getControlledLedID();
};

#endif
