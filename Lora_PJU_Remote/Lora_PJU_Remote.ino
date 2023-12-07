#define debugMode 1
#if debugMode == 1
#define debug(x) Serial.println(x)
#else
#define debug(x)
#endif

//String data;
String devAddr;
String appSKey;
String nwkSKey;
String ssid_wifi_ap, pass_wifi_ap, http_username, http_password;
int classTx;
int sfTx;
int powerTx;
int channelTx;
int uplinkInterval;
bool irFlag = true;
void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200); /* Define baud rate for serial communication */
  Serial2.begin(2400, SERIAL_8N1, 16, 17);
  ledcSetup(1, 38000, 8);
  ledcAttachPin(25, 1);  //Red
  ledcWrite(1, 127);

  spiffSetup();
  readSettings();
  serverSetup();
}


void loop() {
  if (irFlag == true) {
    static unsigned long prevMillis = 0;
    if (millis() - prevMillis >= 100) {
      Serial2.print("z");  //untuk membuat receiver masuk ke mode download
      prevMillis = millis();
    }
  }
}
