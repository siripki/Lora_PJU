void rgbSetup(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){
  ledcSetup(1, 500, 8);
  ledcSetup(2, 500, 8);
  ledcSetup(3, 500, 8);
  ledcAttachPin(redPin, 1); //Red
  ledcAttachPin(greenPin, 2); //Green
  ledcAttachPin(bluePin, 3); //Blue
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}
void turnOnRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t blinkCount, uint16_t ledInterval) {
  if (blinkCount == 0 && ledInterval == 0){
    ledcWrite(1, red);
    ledcWrite(2, green);
    ledcWrite(3, blue);
  }
  else if (blinkCount == 0 && ledInterval != 0){
    ledcWrite(1, red);
    ledcWrite(2, green);
    ledcWrite(3, blue);
    delay(ledInterval);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  }
  for (uint8_t i = 0; i<blinkCount; i++) {
    ledcWrite(1, red);
    ledcWrite(2, green);
    ledcWrite(3, blue);
    delay(ledInterval);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
    delay(ledInterval);
  }
}
void turnOffRGB(){
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}