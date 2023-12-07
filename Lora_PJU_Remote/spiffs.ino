#include "SPIFFS.h"
#include "FS.h"

void spiffSetup(){
  if(!SPIFFS.begin(true)){
      debug("SPIFFS Mount Failed");
    return;
  }
}

String readFile(const char *path) {
  File file = SPIFFS.open(path,"r");
  if(!file){
    debug("Failed to open file for reading");
    return String();
  }
  String fileContent;
  while(file.available()){
    fileContent +=(char)file.read();
  }
  file.close();
  return fileContent;
}

void writeFile(const char * path, const char * fileContent){
    File file = SPIFFS.open(path, FILE_WRITE);
    /*if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }*/
    if(file.print(fileContent)){
        debug("- file written");
    } else {
        debug("- write failed");
    }
    file.close();
}

void readSettings() {
  String data;
  data = readFile("/parameter.txt");
  decodeJson(data);
  if (devAddr == "" && appSKey == "" && nwkSKey == "") {
    dataDefault();
    data = readFile("/parameter.txt");
  }
  decodeJson(data);
  ssid_wifi_ap = readFile("/ssid_wifi_ap.txt");
  pass_wifi_ap = readFile("/pass_wifi_ap.txt");
  http_username = readFile("/http_username.txt");
  http_password = readFile("/http_password.txt");

  debug("devAddr        :" + devAddr);
  debug("appSKey        :" + appSKey);
  debug("nwkSKey        :" + nwkSKey);
  debug("classTx        :" + String(classTx));
  debug("sfTx           :" + String(sfTx));
  debug("powerTx        :" + String(powerTx));
  debug("channelTx      :" + String(channelTx));
  debug("uplinkInterval :" + String(uplinkInterval));
}

void dataDefault() {
  const char* jsonString = "{"
                      "\"dev\": \"650ec8e6\","
                      "\"app\": \"650ec8e61560703382efffc1fec28417\","
                      "\"nwk\": \"650ec8e6a984a2207933fb43666b0d34\","
                      "\"clsTx\": 1,"
                      "\"sfTx\": 12,"
                      "\"pTx\": 20,"
                      "\"cTx\": 1,"
                      "\"upIn\": 15"
                      "}";
  writeFile("/parameter.txt", jsonString);
  writeFile("/ssid_wifi_ap.txt", "PJU Remote");
  writeFile("/pass_wifi_ap.txt", "12345678");
  writeFile("/http_username.txt", "admin");
  writeFile("/http_password.txt", "admin");
}