/*
 NeoColor.cpp
 */
#include "NeoColor.h"
#include <Adafruit_NeoPixel.h>

NeoColor::NeoColor(float red, float green, float blue) {
	_red = red;
	_green = green;
	_blue = blue;
}

void NeoColor::set(float red, float green, float blue) {
	_red = red;
	_green = green;
	_blue = blue;
}

uint32_t NeoColor::getFinalColor() {

	return (applyBounds(_red) << 16) | (applyBounds(_green) <<  8) | applyBounds(_blue);
}

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