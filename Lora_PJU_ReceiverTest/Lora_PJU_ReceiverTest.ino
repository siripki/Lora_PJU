String devAddr;  // "uui24424"
String appSKey;
String nwkSKey;
int classTx;
int sfTx;
int powerTx;
int channelTx;
int uplinkInterval;

void setup() {
  rgbSetup(2, 14, 15);
  spiffSetup();
  Serial.begin(115200); /* Define baud rate for serial communication */
  irSetup();
  if (getDataIR() == false){
    readSettings();
  }
}

void loop() {
  Serial.println("ini DevAdd  : \"" + String(devAddr)+"\"");
  Serial.println("ini appAdd  : \"" + String(appSKey)+"\"");
  Serial.println("ini newk    : \"" + String(nwkSKey)+"\"");
  Serial.println("ini cTx     : " + String(classTx));
  Serial.println("ini sfTx    : " + String(sfTx));
  Serial.println("ini pwrTx   : " + String(powerTx));
  Serial.println("ini chTx    : " + String(channelTx));
  Serial.println("ini upInter : " + String(uplinkInterval));
  delay(20000);
}