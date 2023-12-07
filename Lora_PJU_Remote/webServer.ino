#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

void serverSetup() {
  WiFi.softAP(ssid_wifi_ap.c_str(), pass_wifi_ap.c_str());
  // Serve Static File on Assets
  server.serveStatic("/assets/", SPIFFS, "/assets/");

  // Default Handler 404
  server.onNotFound([](AsyncWebServerRequest* request) {
    request->redirect("/assets/index.htm");
  });

  // Handle Default URI
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    //readSettings();
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // execute : Handle post request
  server.on("/execute", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->authenticate(http_username.c_str(), http_password.c_str())) {
      if (request->hasParam("devAddr", true) and request->hasParam("appSKey", true) and request->hasParam("nwkSKey", true) and request->hasParam("class_tx", true) and request->hasParam("sf_tx", true) and request->hasParam("power_tx", true) and request->hasParam("channel_tx", true) and request->hasParam("interval_uplink", true)) {
        devAddr = request->getParam("devAddr", true)->value();
        appSKey = request->getParam("appSKey", true)->value();
        nwkSKey = request->getParam("nwkSKey", true)->value();
        classTx = (request->getParam("class_tx", true)->value()).toInt();
        sfTx = (request->getParam("sf_tx", true)->value()).toInt();
        powerTx = (request->getParam("power_tx", true)->value()).toInt();
        channelTx = (request->getParam("channel_tx", true)->value()).toInt();
        uplinkInterval = (request->getParam("interval_uplink", true)->value()).toInt();
        irFlag = false;
        sendJson();
        String dataJson;
        codeJson(dataJson);
        writeFile("/parameter.txt", dataJson.c_str());
        irFlag = true;
      }

      else if (request->hasParam("ssid_wifi_ap", true) and request->hasParam("pass_wifi_ap", true)) {
        ssid_wifi_ap = request->getParam("ssid_wifi_ap", true)->value();
        pass_wifi_ap = request->getParam("pass_wifi_ap", true)->value();

        writeFile("/ssid_wifi_ap.txt", ssid_wifi_ap.c_str());
        writeFile("/pass_wifi_ap.txt", pass_wifi_ap.c_str());
      }

      else if (request->hasParam("http_username", true) and request->hasParam("http_password", true)) {
        http_username = request->getParam("http_username", true)->value();
        http_password = request->getParam("http_password", true)->value();

        writeFile("/http_username.txt", http_username.c_str());
        writeFile("/http_password.txt", http_password.c_str());
      }


      delay(50);
      //readSettings();
      request->redirect("/");
      Serial.println("Execute OK!");
    } else {
      delay(50);
      request->send(200, "text/plain", "You don't have permission!");
      Serial.println("Execute ERROR First!");
    }
  });

  // Logout Page With Authentication
  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", "Success Logout!");
  });

  // Logout Without Authentication Process
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(401);
  });

  server.begin();
  digitalWrite(2, HIGH);
}


String processor(const String& var) {
  if (var == "http_username") {
    return http_username;
  } else if (var == "http_password") {
    return http_password;
  } else if (var == "ssid_wifi_ap") {
    return ssid_wifi_ap;
  } else if (var == "pass_wifi_ap") {
    return pass_wifi_ap;
  }

  else if (var == "devAddr") {
    return devAddr;
  } else if (var == "appSKey") {
    return appSKey;
  } else if (var == "nwkSKey") {
    return nwkSKey;
  } else if (var == "class_tx") {
    return String(classTx);
  } else if (var == "sf_tx") {
    return String(sfTx);
  } else if (var == "power_tx") {
    return String(powerTx);
  } else if (var == "channel_tx") {
    return String(channelTx);
  } else if (var == "interval_uplink") {
    return String(uplinkInterval);
  }
  else {
    return String();
  }
}
