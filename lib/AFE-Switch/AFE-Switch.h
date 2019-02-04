/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#ifndef _AFE_Switch_h
#define _AFE_Switch_h

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

class AFESwitch {

private:
  SWITCH SwitchConfiguration;
  boolean _initialized = false;
  boolean state;
  boolean previousState; // Actually this stores current switch state

  unsigned long startTime = 0;

  boolean pressed = false; // It's set to true once button pressed physically
  boolean _pressed = false;

  /* Forst one is set to true after X secodns. Second one controls LED */
  boolean pressed4fiveSeconds = false;
  boolean _pressed4fiveSeconds = false;

  boolean pressed4tenSeconds = false;
  boolean _pressed4tenSeconds = false;

  boolean pressed4thirteenSeconds = false;
  boolean _pressed4thirteenSeconds = false;

  AFELED Led;

public:
  /* Constructors */
  AFESwitch();

  /* Init switch */
  void begin(uint8_t id);

  /* Method: returns TRUE if state of the switch is pressed. It does not mean it
   * has to be pressed physically (applicable for BiStable switch types */
  boolean getState();

  /* Method returns true if switch has been pressed. Sensitiveness it taken into
   * account. It does not mean switch is pressed physically. Once True capture
   * getState() method should be called to get the state of the Switch */
  boolean isPressed();

  /* Method returns true after switch is pressed for 5sec. */
  boolean is5s();

  /* Method return true after switch is pressed for 10sec */
  boolean is10s();

  /* Method return true after switch is pressed for 30sec */
  boolean is30s();

  /* Method has to be added to the loop in order to listen for switch changes */
  void listener();

  uint8_t getFunctionality();
};

#endif
