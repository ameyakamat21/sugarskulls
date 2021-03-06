#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "AJ-Xfin";
const char* password = "<insert-password-here>";

ESP8266WebServer server(80);
#define PIN 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

const int led = LED_BUILTIN;

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
  setStripColor(strip.Color(10, 100, 10));
  server.send(200, "text/plain", "ok");
  strip.show();
}

void neoblue() {
  setStripColor(strip.Color(10, 10, 100));
  server.send(200, "text/plain", "ok");
  strip.show();
}

void neogreen() {
  setStripColor(strip.Color(100, 10, 10));
  server.send(200, "text/plain", "ok");
  strip.show();
}

void setStripColor(uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
   
}

void setPixelStringColor(int pixelNo, String strColor) {
  int number = (int) strtol( &strColor[1], NULL, 16);
  
  // splitting into three parts
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  strip.setPixelColor(pixelNo, strip.Color(g,r,b));
  Serial.print("Set pixel ");
  Serial.print(pixelNo);
  Serial.print(" to ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);
}

void setStripTo() {
  Serial.println("Args: " + server.args());
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
 
}
