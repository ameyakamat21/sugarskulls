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
    void setToNow(uint32_t color);
    void setToGradually(uint8_t red, uint8_t green, uint8_t blue);
    void setDestinationColor(uint8_t red, uint8_t green, uint8_t blue);
    bool updateColor();
    bool floatEqual(float f1, float f2);
    void printColorTriplet(String prefix, float r, float g, float b);
    void printColorTriplet(String prefix, uint8_t r, uint8_t g, uint8_t b);
    void printHex();
    String getHexStr();
  private:
    Adafruit_NeoPixel *_stripPtr;
    int _index;
    unsigned long _lastRecordedMillis;
    float _currRed, _destRed, _deltaRed;
    float _currGreen, _destGreen, _deltaGreen;
    float _currBlue, _destBlue, _deltaBlue;
    float _updateFactor;
    int _changePeriodMs;  // Period under which the color changes 
    int _updatePeriodMs;  // How often an update happens
    void moveTowardDestinationColor();
};

#endif
