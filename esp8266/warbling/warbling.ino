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

ESP8266WebServer server(80);
WebServer webServer;
#define PIN 5
#define NUM_PIXELS 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
Pixel myPixels[NUM_PIXELS];
NeoStrip neoStrip = NeoStrip(&strip, NUM_PIXELS);
unsigned long lastUpdatedMillis = 0;
const int led = LED_BUILTIN;
String printStr = "";

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

//  webServer = WebServer(&server, &neoStrip);
  server.on("/", handleRoot);
  server.on("/ledon", ledOn);
  server.on("/ledoff", ledOff);
  server.on("/neored", neored);
  server.on("/neoblue", neoblue);
  server.on("/neogreen", neogreen);
  server.on("/setstripto", setStripTo);
  server.on("/seteffectparams", handleSetEffectParams);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
//  webServer.handleClient();
  // Update all pixels
  neoStrip.updateColor();
}

