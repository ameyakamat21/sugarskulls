/*
  Pixel.h 
*/

#ifndef Pixel_h
#define Pixel_h

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

class Pixel
{
  public:
    Pixel(Adafruit_NeoPixel strip, int index, uint8_t red, uint8_t green, uint8_t blue);
    Pixel(Adafruit_NeoPixel strip, int index, uint32_t color);
    void setToNow(uint32_t color);
    void setToGradually(uint32_t color);
  private:
    Adafruit_NeoPixel _strip;
    int _index;
    uint32_t _currentColor;
    uint8_t _currRed;
    uint8_t _currGreen;
    uint8_t _currBlue;
};

#endif