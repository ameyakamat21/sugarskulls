/*
WebServer.cpp
*/

#include <functional>
#include "WebServer.h"


WebServer::WebServer() {
}


void WebServer::handleRoot() {
  digitalWrite(_ledPin, 1);
  _espServer.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(_ledPin, 0);
}

WebServer::WebServer(ESP8266WebServer espServer, NeoStrip *neoStrip) {
	_espServer = espServer;
	_neoStrip = neoStrip;


	_espServer.on("/", std::bind(&WebServer::handleRoot, this));
	_espServer.on("/ledon", std::bind(&WebServer::ledOn, this));
	_espServer.on("/ledoff", std::bind(&WebServer::ledOff, this));
	_espServer.on("/neored", std::bind(&WebServer::neored, this));
	_espServer.on("/neoblue", std::bind(&WebServer::neoblue, this));
	_espServer.on("/neogreen", std::bind(&WebServer::neogreen, this));
	_espServer.on("/setstripto", std::bind(&WebServer::setStripTo, this));
	_espServer.onNotFound(std::bind(&WebServer::handleNotFound, this));

	_espServer.begin();
	Serial.println("HTTP server started");
}

void WebServer::handleNotFound(){
  digitalWrite(_ledPin, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += _espServer.uri();
  message += "\nMethod: ";
  message += (_espServer.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += _espServer.args();
  message += "\n";
  for (uint8_t i=0; i<_espServer.args(); i++){
    message += " " + _espServer.argName(i) + ": " + _espServer.arg(i) + "\n";
  }
  _espServer.send(404, "text/plain", message);
  digitalWrite(_ledPin, 0);
}

void WebServer::ledOn() {
  digitalWrite(_ledPin, 0);
  _espServer.send(200, "text/plain", "ok");
}

void WebServer::ledOff() {
  digitalWrite(_ledPin, 1);
  _espServer.send(200, "text/plain", "ok");
}

void WebServer::neored() {
  setStripDestinationColor(100, 10, 10);
  _espServer.send(200, "text/plain", "ok");
}

void WebServer::neoblue() {
  _espServer.send(200, "text/plain", "ok");
  setStripDestinationColor(10, 10, 100);
}

void WebServer::neogreen() {
  _espServer.send(200, "text/plain", "ok");
  setStripDestinationColor(10, 100, 10);
}

void WebServer::setStripDestinationColor(uint8_t red, uint8_t green, uint8_t blue) {
  for(int i=0; i<(*_neoStrip).numPixels(); i++) {
      (*_neoStrip).setPixelDestinationColor(i, red, green, blue);  
  }
}

void WebServer::setPixelStringColor(int pixelNo, String strColor) {
  int number = (int) strtol( &strColor[1], NULL, 16);
  
  // splitting into three parts
  uint8_t r = number >> 16;
  uint8_t g = number >> 8 & 0xFF;
  uint8_t b = number & 0xFF;
  (*_neoStrip).setPixelDestinationColor(pixelNo, r, g, b);
}

void WebServer::setStripTo() {
  String response = "";
  for(int i=0; i<(*_neoStrip).numPixels(); i++) {
    String arg_i = "p" + String(i);
    String color_i = _espServer.arg(arg_i);
    setPixelStringColor(i,color_i);
    response += color_i + " ";
  }
  
  _espServer.send(200, "text/plain", "ok " + response + "\n");
}


