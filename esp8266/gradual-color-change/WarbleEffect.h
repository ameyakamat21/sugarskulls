/*
  WarbleEffect.h 
*/

#ifndef WarbleEffect_h
#define WarbleEffect_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "PixelEffect.h"

class WarbleEffect: PixelEffect
{
public:
	WarbleEffect(float ampl, float periodMs);
private:
	float _ampl;
	float _periodMs;

};

#endif
