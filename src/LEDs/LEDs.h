//
// Created by Paul on 27/01/2024.
//

#ifndef REMOTE4_PIO_REWRITE_LEDS_H
#define REMOTE4_PIO_REWRITE_LEDS_H

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 50
#define LED_PIN 16
#define BRIGHTNESS 40
#define LEDSPERRING 12

extern Adafruit_NeoPixel strip;

void setupStrip();

void setRing(int ring, int n, unsigned char r, unsigned char g, unsigned char b);

void setRingfromMapping(int ring, int n);

void rainbow(int wait);

#endif //REMOTE4_PIO_REWRITE_LEDS_H
