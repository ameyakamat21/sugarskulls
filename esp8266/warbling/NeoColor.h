/*
  NeoColor.h 
*/

#ifndef NeoColor_h
#define NeoColor_h

#include <Adafruit_NeoPixel.h>

class NeoColor
{
public:
	NeoColor();
	NeoColor(float red, float green, float blue);
	float red();
	float green();
	float blue();
	uint32_t getFinalColor();
	void set(float red, float green, float blue);
	void set(uint8_t red, uint8_t green, uint8_t blue);
	void moveTowards(NeoColor destColor, float factor);
	void printHex();
	String getHexStr();
private:
	float _red, _green, _blue;
	uint32_t applyBounds(float comp);
	bool floatEqual(float f1, float f2);
};

#endif
