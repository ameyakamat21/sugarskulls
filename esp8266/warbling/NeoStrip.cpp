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
}


void NeoStrip::setPixelDestinationColor(int pixelNo, uint8_t r, uint8_t g, uint8_t b) {

	_pixels[pixelNo].setDestinationColor(r, g, b);
}

/* 
 * Callback to be called every iteration of main loop to update colors
 */
void NeoStrip::updateColor() {

	for(int i=0; i<_numPixels; i++) {
		_pixels[i].updateColor();
	}
}