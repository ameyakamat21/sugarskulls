/*
  PixelEffect.h 
*/

#ifndef PixelEffect_h
#define PixelEffect_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

class PixelEffect
{
public:
	virtual void updatePixel() = 0;
private:
	float *_currRed, *_currGreen, *_currBlue;

};

#endif
