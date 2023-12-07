#include "SPIFFS.h"
#include "FS.h"

void spiffSetup() {
  if (!SPIFFS.begin(true)) {
    //debug("SPIFFS Mount Failed");
    return;
  }
}

String readFile(const char *path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    //debug("Failed to open file for reading");
    return String();
  }
  String fileContent;
  while (file.available()) {
    fileContent += (char)file.read();
  }
  file.close();
  return fileContent;
}

void writeFile(const char *path, const char *fileContent) {
  File file = SPIFFS.open(path, FILE_WRITE);
  /*if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }*/
  if (file.print(fileContent)) {
    //debug("- file written");
  } else {
    //debug("- write failed");
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
                      "\"upIn\": 1"
                      "}";
  writeFile("/parameter.txt", jsonString);
}