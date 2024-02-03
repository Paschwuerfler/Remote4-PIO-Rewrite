//
// Created by Paul on 26/01/2024.
//

#ifndef REMOTE4_PIO_REWRITE_DISPLAY_H
#define REMOTE4_PIO_REWRITE_DISPLAY_H


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

//Adafruit_SSD1306 display header entry

extern Adafruit_SSD1306 display;


void setupDisplay();



#endif //REMOTE4_PIO_REWRITE_DISPLAY_H
