/*
  WebServer.h 
*/

#ifndef WebServer_h
#define WebServer_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "NeoStrip.h"

class WebServer
{
public:
	WebServer();
	WebServer(ESP8266WebServer espServer, NeoStrip *neoStrip);
	void handleRoot();
	void handleNotFound();
	void ledOn();
	void ledOff();
	void neored();
	void neoblue();
	void neogreen();
	void setStripDestinationColor(uint8_t red, uint8_t green, uint8_t blue);
	void setPixelStringColor(int pixelNo, String strColor);
	void setStripTo();
private:
	ESP8266WebServer _espServer;
	NeoStrip *_neoStrip;
	const int _ledPin = LED_BUILTIN;
};

#endif
