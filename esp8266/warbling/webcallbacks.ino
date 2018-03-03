
void ledOn() {
  digitalWrite(led, 0);
  server.send(200, "text/plain", "ok");
}

void ledOff() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "ok");
}

void neored() {
  setStripDestinationColor(100, 10, 10);
  server.send(200, "text/plain", "ok");
}

void neoblue() {
  server.send(200, "text/plain", "ok");
  setStripDestinationColor(10, 10, 100);
}

void neogreen() {
  server.send(200, "text/plain", "ok");
  setStripDestinationColor(10, 100, 10);
}


void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setStripDestinationColor(uint8_t red, uint8_t green, uint8_t blue) {
  for(int i=0; i<strip.numPixels(); i++) {
      neoStrip.setPixelDestinationColor(i, red, green, blue);  
  }
}

void setPixelStringColor(int pixelNo, String strColor) {
  int number = (int) strtol( &strColor[1], NULL, 16);
  
  // splitting into three parts
  uint8_t r = number >> 16;
  uint8_t g = number >> 8 & 0xFF;
  uint8_t b = number & 0xFF;
  neoStrip.setPixelDestinationColor(pixelNo, r, g, b);
}

void setStripTo() {
  String response = "";
  for(int i=0; i<NUM_PIXELS; i++) {
    String arg_i = "p" + String(i);
    String color_i = server.arg(arg_i);
    setPixelStringColor(i,color_i);
    response += color_i + " ";
  }
  strip.show();
  server.send(200, "text/plain", "ok " + response + "\n");
}
