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
  	Pixel();
    Pixel(Adafruit_NeoPixel *strip, int index, uint8_t red, uint8_t green, uint8_t blue);
    Pixel(Adafruit_NeoPixel *strip, int index, uint32_t color);
    void setToNow(uint32_t color);
    void setToGradually(uint8_t red, uint8_t green, uint8_t blue);
    void setDestinationColor(uint8_t red, uint8_t green, uint8_t blue);
  private:
    Adafruit_NeoPixel *_stripPtr;
    int _index;
    uint32_t _currentColor;
    float _currRed, _destRed, _deltaRed;
    float _currGreen, _destGreen, _deltaGreen;
    float _currBlue, _destBlue, _deltaBlue;
    int _changePeriodMs;  // Period under which the color changes 
    int _updatePeriodMs;  // How often an update happens
};

#endif
