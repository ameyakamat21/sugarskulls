/*
  WarbleEffect.h 
*/

#ifndef WarbleEffect_h
#define WarbleEffect_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "PixelEffect.h"
#include "NeoColor.h"

class WarbleEffect
{
public:
	WarbleEffect();
	WarbleEffect(float ampl, float periodMs);
	void updateAmplitude(float ampl);
	void updatePeriod(float period);
	void applyWarble(NeoColor *endEffectColor, NeoColor baseColor);
private:
	float _ampl;
	float _periodMs;
	int _redDirection, _greenDirection, _blueDirection;
};

#endif
