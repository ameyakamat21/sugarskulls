/*
  PixelEffect.h 
*/

#ifndef PixelEffect_h
#define PixelEffect_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>


// TODO implement effect chain: a linked list of effects

class PixelEffect
{
public:
	virtual void updatePixel() = 0;
private:

};

#endif
