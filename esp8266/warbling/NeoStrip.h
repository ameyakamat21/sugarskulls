/*
  NeoStrip.h 
*/

#ifndef NeoStrip_h
#define NeoStrip_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "Pixel.h"

class NeoStrip
{
public:
	NeoStrip(Adafruit_NeoPixel *stripPtr, int numPixels);
	void updateColor();
	void setPixelDestinationColor(int pixelNo, uint8_t r, uint8_t g, uint8_t b);
	void setPixelEffect(int pixelNo, int warbPeriodMs, int warbAmpl);
	int numPixels();
private:
	Adafruit_NeoPixel *_stripPtr;
	int _numPixels;
	// Array of Pixel pointers
	Pixel *_pixels;
};

#endif
