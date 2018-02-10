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
  _currRed = (float) red;
  _currGreen = (float) green;
  _currBlue = (float) blue;
  _changePeriodMs = 1000; //ms
  _updatePeriodMs = 20; //ms
}

void Pixel::setToNow(uint32_t color)
{
  // Set color now
  (*_stripPtr).setPixelColor(_index, color);
}

void Pixel::setToGradually(uint8_t red, uint8_t green, uint8_t blue)
{
  // Set to eventually


  for(int i = 0; i < 50; i++) {
    green = (green + 10) % 256;
    red = (red + 10) % 256;
    blue = (red + 10) % 256;
    (*_stripPtr).setPixelColor(_index, (*_stripPtr).Color(green, red, blue));
    (*_stripPtr).show();
    delay(20);
  }
}

void Pixel::setDestinationColor(uint8_t red, uint8_t green, uint8_t blue)
{
  // Set to eventually
}

