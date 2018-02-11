#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "Pixel.h"

const char* ssid = "AJ-Xfin";
const char* password = "<ins-here>";

ESP8266WebServer server(80);
#define PIN 5
#define NUM_PIXELS 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
Pixel myPixels[NUM_PIXELS];
unsigned long lastUpdatedMillis = 0;
const int led = LED_BUILTIN;
String printStr = "";

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

void setStripDestinationColor(uint8_t red, uint8_t green, uint8_t blue) {
  for(int i=0; i<strip.numPixels(); i++) {
      myPixels[i].setDestinationColor(red, green, blue);
    }
}

void setPixelStringColor(int pixelNo, String strColor) {
  int number = (int) strtol( &strColor[1], NULL, 16);
  
  // splitting into three parts
  uint8_t r = number >> 16;
  uint8_t g = number >> 8 & 0xFF;
  uint8_t b = number & 0xFF;
  myPixels[pixelNo].setDestinationColor(r,g,b);
//  strip.setPixelColor(pixelNo, strip.Color(g,r,b));
}

void setStripTo() {
  String c0 = server.arg("p0");
  setPixelStringColor(0,c0);
  String c1 = server.arg("p1");
  setPixelStringColor(1,c1);
  String c2 = server.arg("p2");
  setPixelStringColor(2,c2);
  String c3 = server.arg("p3");
  setPixelStringColor(3,c3);
  String c4 = server.arg("p4");
  setPixelStringColor(4,c4);
  strip.show();
  server.send(200, "text/plain", "ok " + c0 + " " + c1 + " " + c2 + " " + c3 + " " + c4 + "\n");
}

void setup(void){
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hey whats up you guyz Matry Schwartz here");

  // WiFi init
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(led, 1);

  // Init neopixel strip
  strip.begin();
  strip.show();

  Serial.println(" - Initializing Pixel array");
  for(uint8_t i=0; i<5; i++) {
    myPixels[i] = Pixel(&strip, i, 100, 200, 150);
  }
  
  Serial.println(" - Finished initializing Pixel array");

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ledon", ledOn);
  server.on("/ledoff", ledOff);
  server.on("/neored", neored);
  server.on("/neoblue", neoblue);
  server.on("/neogreen", neogreen);
  server.on("/setstripto", setStripTo);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  // Update all pixels
  bool updated = false;
  printStr = "";
  for(int i=0; i<NUM_PIXELS; i++) {
    updated = updated || myPixels[i].updateColor();
    printStr += myPixels[i].getHexStr();
  }
  if(updated)  {
    Serial.println(printStr);
  }
}

