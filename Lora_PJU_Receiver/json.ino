#include <ArduinoJson.h>
StaticJsonDocument<384> doc;

void decodeJson(String data) {
  //Serial.println(data);
  DeserializationError error = deserializeJson(doc, data);
  const char *tempdevAddr = doc["dev"];
  devAddr = tempdevAddr;
  const char *tempappSKey = doc["app"];
  appSKey = tempappSKey;
  const char *tempnwkSKey = doc["nwk"];
  nwkSKey = tempnwkSKey;
  classTx = doc["clsTx"];
  sfTx = doc["sfTx"];
  powerTx = doc["pTx"];
  channelTx = doc["cTx"];
  uplinkInterval = doc["upIn"];
}