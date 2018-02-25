/*
  Pixel.cpp 
*/

// Ex: curl -X POST -d "p0=#93EDDC&p1=#F9FCA6&p2=#8661f4&p3=#0000AA&p4=#050505" 10.0.0.203:80/setstripto

#include "Pixel.h"

Pixel::Pixel() {

}

Pixel::Pixel(Adafruit_NeoPixel *stripPtr, int index, uint8_t red, uint8_t green, uint8_t blue) {
  Serial.print(" -- In Pixel::Pixel constructor #");
  Serial.println(index);
  _lastRecordedMillis = millis();
  _stripPtr = stripPtr;
  _index = index;
  _currColor = NeoColor((float) red, (float) green, (float) blue);
  _destColor = NeoColor((float) red, (float) green, (float) blue);
  _endEffectColor = NeoColor((float) red, (float) green, (float) blue);

  _changePeriodMs = 1000; //ms
  _updatePeriodMs = 25; //ms
  _updateFactor = 0.25;
}

void Pixel::setToNow(uint32_t color)
{
  // Set color now
  (*_stripPtr).setPixelColor(_index, color);
}


void Pixel::setDestinationColor(uint8_t red, uint8_t green, uint8_t blue)
{
  _destColor.set(red, green, blue);
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

   (*_stripPtr).setPixelColor(_index, _currColor.getFinalColor());
   (*_stripPtr).show();
   return true;
}

void Pixel::moveTowardDestinationColor() {
  _currColor.moveTowards(_destColor, _updateFactor);
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
  _currColor.printHex();
}

// Print the current red, green, blue values as a hex string 
String Pixel::getHexStr() {
   return _currColor.getHexStr();
}


