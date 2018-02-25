#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "Pixel.h"
#include "NeoStrip.h"
#include "WebServer.h"

const char* ssid = "AJ-Xfin";
const char* password = "<ins-here>";

WebServer webServer;
ESP8266WebServer server(80);
#define PIN 5
#define NUM_PIXELS 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
Pixel myPixels[NUM_PIXELS];
NeoStrip neoStrip = NeoStrip(&strip, NUM_PIXELS);
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
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

//  webServer = WebServer(server, &neoStrip);
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
  neoStrip.updateColor();
}

