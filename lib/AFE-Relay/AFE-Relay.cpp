/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: https://www.smartnydom.pl/afe-firmware-pl/ */

#include "AFE-Relay.h"

AFERelay::AFERelay(){};

void AFERelay::begin(uint8_t id) {
  _id = id;
  RelayConfiguration = Data.getRelayConfiguration(_id);

  pinMode(RelayConfiguration.gpio, OUTPUT);

  if (RelayConfiguration.ledID > 0) {
    Led.begin(RelayConfiguration.ledID - 1);
  }
}

byte AFERelay::get() {
  return digitalRead(RelayConfiguration.gpio) == HIGH ? RELAY_ON : RELAY_OFF;
}

/* Set relay to ON */
void AFERelay::on(boolean invert) {
  if (get() == RELAY_OFF) {
    digitalWrite(RelayConfiguration.gpio, HIGH);
    Led.on();
  }
  Data.saveRelayState(_id, RELAY_ON);
}

/* Set relay to OFF */
void AFERelay::off(boolean invert) {
  if (get() == RELAY_ON) {
    digitalWrite(RelayConfiguration.gpio, LOW);
    Led.off();
  }
  Data.saveRelayState(_id, RELAY_OFF);
}

uint8_t AFERelay::getControlledLedID() { return RelayConfiguration.ledID; }
