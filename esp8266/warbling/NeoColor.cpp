/*
 NeoColor.cpp
 */
#include "NeoColor.h"
#include <Adafruit_NeoPixel.h>


NeoColor::NeoColor() {
}

NeoColor::NeoColor(float red, float green, float blue) {
	_red = red;
	_green = green;
	_blue = blue;
}
/* Getters */
float NeoColor::red() {
	return _red;
}

float NeoColor::green() {
	return _green;
}

float NeoColor::blue() {
	return _blue;
}

void NeoColor::set(float red, float green, float blue) {
	_red = red;
	_green = green;
	_blue = blue;
}

void NeoColor::set(uint8_t red, uint8_t green, uint8_t blue) {
	_red = (float) red;
	_green = (float) green;
	_blue = (float) blue;
}


void NeoColor::moveTowards(NeoColor destColor, float updateFactor) {
	if(!floatEqual(_blue, destColor.blue())) {
	  _blue += (destColor.blue() - _blue) * updateFactor;
	}
	if(!floatEqual(_green, destColor.green())) {
	  _green += (destColor.green() - _green) * updateFactor;
	}
	if(!floatEqual(_red, destColor.red())) {
	  _red += (destColor.red() - _red) * updateFactor;
	}
}

uint32_t NeoColor::getFinalColor() {

	return (applyBounds(_green) << 16) | (applyBounds(_red) <<  8) | applyBounds(_blue);
}

/* Private methods */

/* 
Casts comp to a uint32_t, ensuring it is in the bounds [0,255]
*/
uint32_t NeoColor::applyBounds(float comp) {
	if(comp > 255.0) {
		return 255;
	} else if(comp < 0.0) {
		return 0;
	} else {
		return ((uint32_t) comp) & 0xFF;
	}
}

bool NeoColor::floatEqual(float f1, float f2) {
  return abs(f1 - f2) < 1;
}

void NeoColor::printHex() {
#ifdef DEBUG
   Serial.print(String(getFinalColor(),HEX) + ", ");
#endif
}

// Print the current red, green, blue values as a hex string 
String NeoColor::getHexStr() {
   return (String(getFinalColor(),HEX) + ", ");
}