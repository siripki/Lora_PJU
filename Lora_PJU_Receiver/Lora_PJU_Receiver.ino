/*Lora PJU Beta
Changelog:
- add library to sub sketch folder
- modified ina219 library
- improve rgb setup
- add SPIFFS
*/
#define debugMode 1
#if debugMode == 1
#define debug(x) Serial.println(x)
#else
#define debug(x)
#endif

//global variabel
float shuntVoltage_mV = 0.0;
float loadVoltageV = 0.0;
float busVoltageV = 0.0;
float currentA = 0.0;
float powerWh = 0.0;
float energy = 0.0;
float chargingEnergy = 0.0;
String devAddr;
String appSKey;
String nwkSKey;
int classTx;
int sfTx;
int powerTx;
int channelTx;
uint8_t uplinkInterval;  //in minute

void setup() {
  Serial.begin(115200);
  rgbSetup(2, 14, 15);
  spiffSetup();
  irSetup();
  //if (getDataIR() == false) {
    readSettings();
  //}
  //#if debugMode == 1
  debug("devAddr        :" + String(devAddr));
  debug("appSKey        :" + String(appSKey));
  debug("nwkSKey        :" + String(nwkSKey));
  debug("classTx        :" + String(classTx));
  debug("sfTx           :" + String(sfTx));
  debug("powerTx        :" + String(powerTx));
  debug("channelTx      :" + String(channelTx));
  debug("uplinkInterval :" + String(uplinkInterval));
  //#endif
  inaSetup(0.05);
  loraSetup();
  turnOnRGB(0, 255, 0, 3, 100);
}

void loop() {
  inaMeasurement();
  static unsigned long prevMillis2 = 0;
  if (millis() - prevMillis2 >= 60000 * uplinkInterval) {
    if (currentA < 0.0) {
      currentA = sqrt(currentA * currentA);
      sendData_Lora("{\"V\":" + String(loadVoltageV, 1) + ",\"Iin\":" + String(currentA, 1) + ",\"Pin\":" + String(powerWh, 2) + ",\"Ein\":" + String(chargingEnergy, 2) + "}", "Data Dikirim");
    } else {
      sendData_Lora("{\"V\":" + String(loadVoltageV, 1) + ",\"I\":" + String(currentA, 1) + ",\"P\":" + String(powerWh, 2) + ",\"E\":" + String(energy, 2) + "}", "Data Dikirim");
    }
    prevMillis2 = millis();
  }
}
