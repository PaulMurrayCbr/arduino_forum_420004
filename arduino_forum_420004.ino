#include <Adafruit_NeoPixel.h>

const int NUMPIXELS = 24;
const uint32_t CYCLE_MS = 1000;
const float COLOR_R = 0;
const float COLOR_G = 0;
const float COLOR_B = 255;

const byte PIN = 6;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int currentPos = -1; // force an initial show

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  if (!pixels.canShow()) return;

  // this will hiccup when millis rolls over, but meh
  int pos = (millis() % CYCLE_MS) / (float) CYCLE_MS * (float) NUMPIXELS;

  if (pos == currentPos) return;

  currentPos = pos;

  pixels.clear();

  for (int i = 0; i < NUMPIXELS / 2; i++) {
    float bright = (i / (float)NUMPIXELS);

    // uncomment this for a more abrupt fall-off
    // this in effect does a gamma of .5
    bright *= bright;

    float ppos = (NUMPIXELS * 2 - pos - i) % NUMPIXELS;
    uint32_t color = pixels.Color(
                       COLOR_R * bright,
                       COLOR_G * bright,
                       COLOR_B * bright
                     );
    pixels.setPixelColor(ppos, color);
  }

  pixels.show();

}
