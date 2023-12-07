void irSetup() {
  Serial2.begin(2400);
}

bool getDataIR() {
  String data;
  bool flag1 = false;
  bool flag2 = false;
  unsigned long prevMillis = millis();
  while (millis() - prevMillis <= 1000) {
    if (Serial2.available() > 0) {
      turnOnRGB(0, 0, 255, 0, 0);
      flag1 = true;
      while (flag1 == true) {
        char raw = Serial2.read();
        if (raw == '1') {
          flag2 = true;
          flag1 = false;
        }
      }
      while (flag2 == true) {
        while (Serial2.available() > 0) {
          turnOnRGB(255, 0, 255, 1, 1);
          char d = Serial2.read();
          data += d;
          if (d == '}') {
            Serial2.end();
            flag2 = false;
            turnOnRGB(0, 255, 0, 2, 100);
            turnOnRGB(0, 255, 0, 0, 1000);
          }
        }
        writeFile("/parameter.txt", data.c_str());
        decodeJson(data);
      }
      return true;
    }
  }
  return false;
}