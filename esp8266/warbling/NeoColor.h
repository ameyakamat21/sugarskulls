/*
  NeoColor.h 
*/

#ifndef NeoColor_h
#define NeoColor_h

#include <Adafruit_NeoPixel.h>

class NeoColor
{
public:
	NeoColor(float red, float green, float blue);
	float getRed();
	float getGreen();
	float getBlue();
	uint32_t getFinalColor();
	void set(float red, float green, float blue);
private:
	float _red, _green, _blue;
	uint32_t applyBounds(float comp);
};

#endif
