/*
  NeoStrip.cpp 
*/

#include "NeoStrip.h"
#include <ESP8266WiFi.h>


NeoStrip::NeoStrip(Adafruit_NeoPixel *stripPtr, int numPixels) {
	_stripPtr = stripPtr;
	_numPixels = numPixels;
	_pixels = new Pixel[numPixels];

	// Assign initial colors
	for(int i = 0; i<numPixels; i++) {
		_pixels[i] = Pixel(stripPtr, i, 100, 200, 150);
	}

	// Initialize strip
	(*stripPtr).begin();
  	(*stripPtr).show();
}


void NeoStrip::setPixelDestinationColor(int pixelNo, uint8_t r, uint8_t g, uint8_t b) {

	_pixels[pixelNo].setDestinationColor(r, g, b);
}

void NeoStrip::setPixelEffect(int pixelNo, int warbPeriodMs, int warbAmpl) {
	_pixels[pixelNo].setEffect(warbPeriodMs, warbAmpl);
}

/* 
 * Callback to be called every iteration of main loop to update colors
 */
void NeoStrip::updateColor() {
	bool updated = false;
 	String printStr = "";
	for(int i=0; i<_numPixels; i++) {

		updated = updated || _pixels[i].updateColor();
	   	printStr += _pixels[i].getHexStr();
	}

	#ifdef DEBUG
	 if(updated)  {
	   Serial.println(printStr);
	 }
	#endif
}

int NeoStrip::numPixels() {
	return _numPixels;
}