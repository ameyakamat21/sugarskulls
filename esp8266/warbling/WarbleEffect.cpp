/*
  WarbleEffect.cpp 
*/

#include "WarbleEffect.h"
#include "NeoColor.h"

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define PI 3.1415

WarbleEffect::WarbleEffect() {
}

WarbleEffect::WarbleEffect(float ampl, float periodMs) {
	_ampl = ampl;
	_periodMs = periodMs;

	// Randomly either -1, 0, or 1
	_redDirection = 1-2*random(1);
	_greenDirection = 1-2*random(1);
	_blueDirection = 1-2*random(1);
}

void WarbleEffect::updateAmplitude(float ampl) {
	_ampl = ampl;
}

void WarbleEffect::updatePeriod(float periodMs) {
	_periodMs = periodMs;
}

void WarbleEffect::applyWarble(NeoColor *endEffectColor, NeoColor baseColor) {
	unsigned long t = millis();
	float newRed = baseColor.red() + _redDirection * _ampl * sin(2*PI*t/_periodMs);
	float newGreen = baseColor.green() + _greenDirection * _ampl * sin(2*PI*t/_periodMs);
	float newBlue = baseColor.blue() + _blueDirection * _ampl * sin(2*PI*t/_periodMs);
	(*endEffectColor).set(newRed, newGreen, newBlue); 
}
