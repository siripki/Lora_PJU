#include <ArduinoJson.h>
StaticJsonDocument<320> doc;

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

void codeJson(String &dataJson) {
  doc["dev"] = devAddr;
  doc["app"] = appSKey;
  doc["nwk"] = nwkSKey;
  doc["clsTx"] = classTx;
  doc["sfTx"] = sfTx;
  doc["pTx"] = powerTx;
  doc["cTx"] = channelTx;
  doc["upIn"] = uplinkInterval;

  serializeJson(doc, dataJson);
}

void sendJson() {
  bool flag = false;
  flag = true;
  while (flag == true) {
    delay(500);
    Serial2.print("1");  //membuat reciver siap menerima JSON (beri delay)
    delay(500);
    Serial2.print("{\"dev\":\"" + String(devAddr) + "\"");
    delay(300);
    Serial2.print(",\"app\":\"" + String(appSKey) + "\"");
    delay(300);
    Serial2.print(",\"nwk\":\"" + String(nwkSKey) + "\"");
    delay(300);
    Serial2.print(",\"clsTx\":" + String(classTx) + ",\"sfTx\":" + String(sfTx) + ",\"pTx\":" + String(powerTx) + ",\"cTx\":" + String(channelTx) + ",\"upIn\":" + String(uplinkInterval) + "}");
    flag = false;
  }
}