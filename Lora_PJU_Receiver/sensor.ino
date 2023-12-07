#include <Wire.h>
#include "src\INA219_WE\INA219_WE.h"
#define I2C_ADDRESS 0x40
INA219_WE ina219 = INA219_WE(I2C_ADDRESS);

void inaSetup(float rShunt) {
  Wire.begin();
  if (!ina219.init()) {
    debug("Problem : INA219");
  }
  ina219.setShuntSizeInOhms(rShunt);  // Insert your shunt size in ohms
}

void inaMeasurement() {
  shuntVoltage_mV = ina219.getShuntVoltage_mV();
  busVoltageV = ina219.getBusVoltage_V();
  currentA = ina219.getCurrent_A();
  powerWh = ina219.getBusPower_Wh();
  loadVoltageV = busVoltageV + (shuntVoltage_mV / 1000);
  energy = ina219.getEnergy();  //Wh
  chargingEnergy = ina219.getChargingEnergy();
  #if debugMode == 1
  static unsigned long prevMillis = 0;
  if (millis() - prevMillis >= 2000) {
    debug("Shunt Voltage [mV]: " + String(shuntVoltage_mV, 3));
    debug("Bus Voltage [V]   : " + String(busVoltageV, 3));
    debug("Load Voltage [V]  : " + String(loadVoltageV, 3));
    debug("Current[A]        : " + String(currentA, 3));
    debug("Bus Power [W]     : " + String(powerWh, 3));
    debug("Energy [Wh]       : " + String(energy, 3));
    debug("ChargEnergy [Wh]  : " + String(chargingEnergy, 3));
    debug(" ");
    prevMillis = millis();
  }
  #endif
}