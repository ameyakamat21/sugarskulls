/*
  Pixel.cpp 
*/

#include "Pixel.h"

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

Pixel::Pixel(Adafruit_NeoPixel strip, int index, uint32_t color)
{
  _strip = strip;
  _index = index;
  _currentColor = color;

  // TODO set color now
}

Pixel::Pixel(Adafruit_NeoPixel strip, int index, uint8_t red, uint8_t green, uint8_t blue) {
  _strip = strip;
  _index = index;
  _currRed = red;
  _currGreen = green;
  _currBlue = blue;
}

void Pixel::setToNow(uint32_t color)
{
  // Set color now
  _strip.setPixelColor(_index, color);
}

void Pixel::setToGradually(uint32_t color)
{
  // Set to eventually
}

