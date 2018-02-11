/*
  WarbleEffect.cpp 
*/

#include "WarbleEffect.h"

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>


WarbleEffect::WarbleEffect(float ampl, float periodMs) {
	_ampl = ampl;
	_periodMs = periodMs;
}