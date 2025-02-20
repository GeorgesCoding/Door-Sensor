#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED 16
#define numLEDS 100

Adafruit_NeoPixel pixel(numLEDS, LED, NEO_GRB + NEO_KHZ800);

void setColour(int red, int green, int blue);

void setup()
{
  pixel.begin();
}

void loop()
{
  for (int r = 255; r > 0; r--)
  {
    setColour(r, 255 - r, 0);
    pixel.show();
  }
  for (int g = 255; g > 0; g--)
  {
    setColour(0, g, 255 - g);
    pixel.show();
  }
  for (int b = 255; b > 0; b--)
  {
    setColour(255 - b, 0, b);
    pixel.show();
  }
}

void setColour(int red, int green, int blue)
{
  for (int i = 0; i < numLEDS; i++)
  {
    pixel.setPixelColor(i, pixel.Color(red, green, blue));
  }
}