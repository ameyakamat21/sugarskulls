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
	WarbleEffect(float ampl, float periodMs, float *redPtr, float *greenPtr, float *bluePtr);
	void updateAmplitude(float ampl);
	void updatePeriod(float period);
	void applyWarble(float *redPtr, float *greenPtr, float *bluePtr);
private:
	float _ampl;
	float _periodMs;
	float *_redPtr, *_greenPtr, *_bluePtr;
};

#endif
