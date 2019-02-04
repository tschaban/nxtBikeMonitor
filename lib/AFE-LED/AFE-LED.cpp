/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-LED.h"

AFELED::AFELED() {}

void AFELED::begin(uint8_t id) {
  AFEDevice Device;
  if (Device.configuration.isLED[id]) {
    AFEDataAccess Data;
    LEDConfiguration = Data.getLEDConfiguration(id);
    Data = {};
    pinMode(LEDConfiguration.gpio, OUTPUT);
    LEDConfiguration.changeToOppositeValue
        ? digitalWrite(LEDConfiguration.gpio, LOW)
        : digitalWrite(LEDConfiguration.gpio, HIGH);
    _initialized = true;
  }
}

void AFELED::on() {
  if (LEDConfiguration.changeToOppositeValue) {
    set(HIGH);
  } else {
    set(LOW);
  }
}

void AFELED::off() {
  if (LEDConfiguration.changeToOppositeValue) {
    set(LOW);
  } else {
    set(HIGH);
  }
}

void AFELED::blink(unsigned int duration) {
  on();
  delay(duration);
  off();
}

void AFELED::blinkingOn(unsigned long blinking_interval) {
  interval = blinking_interval;
  blinking = true;
}

void AFELED::blinkingOff() { blinking = false; }

boolean AFELED::isBlinking() { return blinking; }

void AFELED::loop() {
  if (_initialized && blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      toggle();
    }
  }
}

void AFELED::set(uint8_t state) {
  if (_initialized) {
    if (digitalRead(LEDConfiguration.gpio) != state) {
      digitalWrite(LEDConfiguration.gpio, state);
    }
  }
}

void AFELED::toggle() {
  if (_initialized) {
    digitalRead(LEDConfiguration.gpio) == HIGH
        ? digitalWrite(LEDConfiguration.gpio, LOW)
        : digitalWrite(LEDConfiguration.gpio, HIGH);
  }
}
