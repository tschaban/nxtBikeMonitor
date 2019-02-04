/* Initializing sensor */
void initSensorNTK10K() {
  if (Device.configuration.isNTK10K) {
    SensorNTK10K.begin();
  }
}

/* Main code for processing sesnor */
void mainSensorNTK10K() {
  if (Device.configuration.isNTK10K) {
    /* Sensor: listener */
    SensorNTK10K.listener();
    if (SensorNTK10K.isReady()) {
      float temperature;
      Led.on();
      temperature = SensorNTK10K.getTemperature();
      Led.off();
    }
  }
}
