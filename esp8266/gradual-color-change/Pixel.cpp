/*
  Pixel.cpp 
*/

#include "Pixel.h"

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

Pixel::Pixel() {

}

Pixel::Pixel(Adafruit_NeoPixel *stripPtr, int index, uint32_t color)
{
  _stripPtr = stripPtr;
  _index = index;
  _currentColor = color;
}

Pixel::Pixel(Adafruit_NeoPixel *stripPtr, int index, uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print(" -- In Pixel::Pixel constructor #");
  Serial.println(index);
  _stripPtr = stripPtr;
  _index = index;
  _currRed = red;
  _currGreen = green;
  _currBlue = blue;
  
}

void Pixel::setToNow(uint32_t color)
{
  // Set color now
  (*_stripPtr).setPixelColor(_index, color);
}

void Pixel::setToGradually(uint32_t color)
{
  // Set to eventually
}

