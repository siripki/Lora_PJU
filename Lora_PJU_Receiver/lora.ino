#include "src\lorawan\lorawan.h"

const sRFM_pins RFM_pins = {
  //board ungu
  .CS = 13,
  .RST = 0,
  .DIO0 = 27,
  .DIO1 = 26,
};

void loraSetup() {
  if (!lora.init()) {
    debug("Problem : Lora");
    delay(5000);
    return;
  }

  switch (classTx) {
    case 1:
      lora.setDeviceClass(CLASS_A);  // Set LoRaWAN Class change CLASS_A
      break;
    case 3:
      lora.setDeviceClass(CLASS_C);  // Set LoRaWAN Class changeCLASS_C
      break;
    default:
      lora.setDeviceClass(CLASS_A);  // Set LoRaWAN Class change CLASS_A
      break;
  }

  switch (sfTx) {
    case 7:
      lora.setDataRate(SF7BW125);
      break;
    case 8:
      lora.setDataRate(SF8BW125);
      break;
    case 9:
      lora.setDataRate(SF9BW125);
      break;
    case 10:
      lora.setDataRate(SF10BW125);
      break;
    case 11:
      lora.setDataRate(SF11BW125);
      break;
    case 12:
      lora.setDataRate(SF12BW125);
      break;
    default:
      lora.setDataRate(SF10BW125);  //default datarate
      break;
  }

  lora.setFramePortTx(5);

  switch (channelTx) {
    case 0:
      lora.setChannel(0);
      break;
    case 1:
      lora.setChannel(1);
      break;
    case 2:
      lora.setChannel(2);
      break;
    case 3:
      lora.setChannel(3);
      break;
    case 4:
      lora.setChannel(4);
      break;
    case 5:
      lora.setChannel(5);
      break;
    case 6:
      lora.setChannel(6);
      break;
    case 7:
      lora.setChannel(7);
      break;
    default:
      lora.setChannel(MULTI);
      break;
  }

  lora.setTxPower(powerTx);
  lora.setNwkSKey(nwkSKey.c_str());
  lora.setAppSKey(appSKey.c_str());
  lora.setDevAddr(devAddr.c_str());
}

void sendData_Lora(String msg, char *msgSeq) {
  char myStr[msg.length() + 1];
  msg.toCharArray(myStr, msg.length() + 1);
  Serial.println(myStr);  //debug
  Serial.println(msgSeq);
  Serial.println(" ");
  lora.sendUplink(myStr, strlen(myStr), 0);
  turnOnRGB(0, 255, 0, 1, 200);
  lora.update();
  //delay(3000);
}