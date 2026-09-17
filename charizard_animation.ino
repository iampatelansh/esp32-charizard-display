#include <TFT_eSPI.h>
#include "sprites.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

#define SPR_W 96
#define SPR_H 64
#define SCALE 1.3   // try 1.5, 2, etc.

#define OUT_W (int)(SPR_W * SCALE)
#define OUT_H (int)(SPR_H * SCALE)

const uint8_t* frames[] = {
  charizard_f1, charizard_f2, charizard_f3, charizard_f4,
  charizard_f5, charizard_f6, charizard_f7, charizard_f8,
  charizard_f9, charizard_f10, charizard_f11
};
const int numFrames = 11;

int currentFrame = 0;
unsigned long lastFrameTime = 0;
const unsigned long frameDelay = 150;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);

  spr.createSprite(OUT_W, OUT_H);
  spr.setSwapBytes(true);
}

void loop() {
  unsigned long now = millis();

  if (now - lastFrameTime >= frameDelay) {
    lastFrameTime = now;

    const uint16_t* pixels = (const uint16_t*)frames[currentFrame];

    for (int y = 0; y < OUT_H; y++) {
      int srcY = y / SCALE;
      for (int x = 0; x < OUT_W; x++) {
        int srcX = x / SCALE;
        uint16_t color = pixels[srcY * SPR_W + srcX];
        spr.drawPixel(x, y, color);
      }
    }

    int x = (160 - OUT_W) / 2;
    int y = (128 - OUT_H) / 2;
    spr.pushSprite(x, y);

    currentFrame = (currentFrame + 1) % numFrames;
  }
}