/* Initializing sensor */
void initSensor() {
  if (Device.configuration.isDS18B20) {
    Sensor.begin();
  }
}

/* Main code for processing sesnor */
void mainSensor() {
  if (Device.configuration.isDS18B20) {
    /* Sensor: listener */
    Sensor.listener();
    if (Sensor.isReady()) {
      Led.on();
      temperature = Sensor.getTemperature();
      Led.off();
    }
  }
}
