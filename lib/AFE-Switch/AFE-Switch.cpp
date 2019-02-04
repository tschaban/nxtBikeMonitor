/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Switch.h"

AFESwitch::AFESwitch(){};

void AFESwitch::begin(uint8_t id) {
  AFEDataAccess Data;
  SwitchConfiguration = Data.getSwitchConfiguration(id);
  pinMode(SwitchConfiguration.gpio, INPUT_PULLUP);
  state = digitalRead(SwitchConfiguration.gpio);
  previousState = state;
  uint8_t systeLedID = Data.getSystemLedID();
  if (systeLedID > 0) {
    Led.begin(systeLedID - 1);
  }
  _initialized = true;
}

boolean AFESwitch::getState() { return state; }

boolean AFESwitch::isPressed() {
  if (pressed) {
    pressed = false;
    return true;
  } else {
    return false;
  }
}

boolean AFESwitch::is5s() {
  if (pressed4fiveSeconds) {
    pressed4fiveSeconds = false;
    return true;
  } else {
    return false;
  }
}

boolean AFESwitch::is10s() {
  if (pressed4tenSeconds) {
    pressed4tenSeconds = false;
    return true;
  } else {
    return false;
  }
}

boolean AFESwitch::is30s() {
  if (pressed4thirteenSeconds) {
    pressed4thirteenSeconds = false;
    return true;
  } else {
    return false;
  }
}

void AFESwitch::listener() {
  if (_initialized) {
    boolean currentState = digitalRead(SwitchConfiguration.gpio);
    unsigned long time = millis();

    if (currentState != previousState) { // buttons has been pressed

      if (startTime == 0) { // starting timer. used for switch sensitiveness
        startTime = time;
      }

      if (time - startTime >=
          SwitchConfiguration.sensitiveness) { // switch prssed, sensitiveness
                                               // taken into account, processing
                                               // event

        if (!_pressed) { // This is set only once when switch is pressed
          state = !state;
          _pressed = true;
          pressed = true;
        }

        /* Code only for Mulitifunction switch: pressed for 5 and 10 seconds
         */
        if (SwitchConfiguration.functionality == SWITCH_MULTI) {

          if (time - startTime >= 35000) {
            Led.blink(50);
            delay(50);
          }

          if (time - startTime >= 30000 && !_pressed4thirteenSeconds) {
            for (uint8_t i = 0; i < 3; i++) {
              Led.blink(200);
              delay(200);
            }
            _pressed4thirteenSeconds = true;
          }

          if (time - startTime >= 10000 && !_pressed4tenSeconds) {
            for (uint8_t i = 0; i < 2; i++) {
              Led.blink(200);
              delay(200);
            }
            _pressed4tenSeconds = true;
          }

          if (time - startTime >= 5000 && !_pressed4fiveSeconds) {
            Led.blink(200);
            _pressed4fiveSeconds = true;
          }
        }
      }

    } else if (currentState == previousState && startTime > 0) {
      /* Code only for Mulitifunction switch: pressed for 5 and 10 seconds */
      if (SwitchConfiguration.functionality == SWITCH_MULTI) {

        if (time - startTime >= 5000 && time - startTime < 10000) {
          pressed4fiveSeconds = true;
        }

        if (time - startTime >= 10000 && time - startTime < 30000) {
          pressed4tenSeconds = true;
        }

        if (time - startTime >= 30000 && time - startTime < 35000) {
          pressed4thirteenSeconds = true;
        }

        _pressed4fiveSeconds = false;
        _pressed4tenSeconds = false;
        _pressed4thirteenSeconds = false;
      }

      startTime = 0;
      _pressed = false;
    }
  }
}

uint8_t AFESwitch::getFunctionality() {
  return SwitchConfiguration.functionality;
}
