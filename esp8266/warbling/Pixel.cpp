/*
  Pixel.cpp 
*/

// Ex: curl -X POST -d "p0=#93EDDC&p1=#F9FCA6&p2=#8661f4&p3=#0000AA&p4=#050505" 10.0.0.203:80/setstripto

#include "Pixel.h"

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

Pixel::Pixel() {

}

Pixel::Pixel(Adafruit_NeoPixel *stripPtr, int index, uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print(" -- In Pixel::Pixel constructor #");
  Serial.println(index);
  _lastRecordedMillis = millis();
  _stripPtr = stripPtr;
  _index = index;
  _currRed = (float) red, _destRed = (float) red, _deltaRed = 0.2;
  _currGreen = (float) green, _destGreen = (float) green, _deltaGreen = 0.2;
  _currBlue = (float) blue, _destBlue = (float) blue, _deltaBlue = 0.2;
  _changePeriodMs = 1000; //ms
  _updatePeriodMs = 25; //ms
  _updateFactor = 0.25;
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
  _destRed = (float) red;
  _destGreen = (float) green;
  _destBlue = (float) blue;

  // *DEPRECATED* Calculate the amount to be added on updateColor() call
  _deltaRed = (_destRed - _currRed) * _updatePeriodMs / _changePeriodMs;
  _deltaGreen = (_destGreen - _currGreen) * _updatePeriodMs / _changePeriodMs;
  _deltaBlue = (_destBlue - _currBlue) * _updatePeriodMs / _changePeriodMs;
}

/* 
 * Call this function every _updatePeriodMs milliseconds
 *
 */
bool Pixel::updateColor() {
   unsigned long currentMillis = millis();
   if(currentMillis - _lastRecordedMillis < _updatePeriodMs) {
    return false;
   }
   _lastRecordedMillis = currentMillis;

   moveTowardDestinationColor();

   // printColorTriplet("curr", (uint8_t) _currRed, (uint8_t) _currGreen, (uint8_t) _currBlue);
   uint32_t newColor = (*_stripPtr).Color((uint8_t) _currGreen, 
                                (uint8_t) _currRed, (uint8_t) _currBlue);
   (*_stripPtr).setPixelColor(_index, newColor);
   (*_stripPtr).show();
   return true;
}

void Pixel::moveTowardDestinationColor() {
  if(!floatEqual(_currBlue, _destBlue)) {
      _currBlue += (_destBlue - _currBlue) * _updateFactor;
   }
   if(!floatEqual(_currRed, _destRed)) {
      _currRed += (_destRed - _currRed) *  _updateFactor;
   }
   if(!floatEqual(_currGreen, _destGreen)) {
      _currGreen += (_destGreen - _currGreen) * _updateFactor;
   }
}

bool Pixel::floatEqual(float f1, float f2) {
  return abs(f1 - f2) < 1;
}

void Pixel::printColorTriplet(String prefix, float r, float g, float b) {
   Serial.println(prefix + ": r = " + String(r) + "; g = " + String(g) + 
                  "; b = " + String(b));
}

void Pixel::printColorTriplet(String prefix, uint8_t r, uint8_t g, uint8_t b) {
  Serial.println(prefix + ": r = " + String(r) + "; g = " + String(g) + 
                  "; b = " + String(b));
}

// Print the current red, green, blue values as a hex string 
void Pixel::printHex() {
#ifdef DEBUG
   uint32_t color = (*_stripPtr).Color((uint8_t) _currGreen, 
                    (uint8_t) _currRed, (uint8_t) _currBlue);
   Serial.print(String(color,HEX) + ", ");
#endif
}

// Print the current red, green, blue values as a hex string 
String Pixel::getHexStr() {
   uint32_t color = (*_stripPtr).Color((uint8_t) _currGreen, 
                    (uint8_t) _currRed, (uint8_t) _currBlue);
   return (String(color,HEX) + ", ");
}


