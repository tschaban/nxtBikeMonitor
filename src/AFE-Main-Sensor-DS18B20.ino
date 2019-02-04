/* Initializing sensor */
void initSensorDS18B20() {
  if (Device.configuration.isDS18B20) {
    SensorDS18B20.begin();
  }
}

/* Main code for processing sesnor */
void mainSensorDS18B20() {
  if (Device.configuration.isDS18B20) {
    /* Sensor: listener */
    SensorDS18B20.listener();
    if (SensorDS18B20.isReady()) {
      Led.on();
      temperature = SensorDS18B20.getTemperature();
      Led.off();
    }
  }
}
