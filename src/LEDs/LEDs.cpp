//
// Created by Paul on 27/01/2024.
//

#include "LEDs.h"
#include "../Bl-HID/Mappings.h"

typedef float d;
typedef d d1;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupStrip() {


    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)

}

void setRing(int ring, int n, unsigned char r, unsigned char g, unsigned char b) {
    //debug("setRing called with ring: " + String(ring) + " n: " + String(n) + " r: " + String(r) + " g: " + String(g) + " b: " + String(b), TRACE);

    for(int i = LEDSPERRING * ring; i < LEDSPERRING * (ring + 1); i ++) {
        if(i < (n + LEDSPERRING * (ring))) {

            strip.setPixelColor(i, r, g, b);
            //Serial.println("Setting Pixel " + String(i) + " to " + String(r) + " " + String(g) + " " + String(b));
        }
        else {
            strip.setPixelColor(i, 0, 0, 0);
            //if(DEBUG == TRACE) Serial.println("Setting Pixel " + String(i) + " to " + String(r) + " " + String(g) + " " + String(b));
        }
    }

}



int generateGradient(int startColor, int endColor, int position, int steps) {
    int color;
    d1 weight = (float) position / (float) steps;
    for(int i = 0; i < 3; i++) {
        color = startColor * (1 - weight) + endColor * weight;
    }
    return color;
}

void colorWipe(uint32_t color, int wait) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        delay(wait);                           //  Pause for a moment
    }
}

void setRingfromMapping(int ring, int n) {
    int colorStart[3] = {mappings[ActiveMapping].color[0][ring][0], mappings[ActiveMapping].color[0][ring][1], mappings[ActiveMapping].color[0][ring][2]};
    int colorEnd[3] = {mappings[ActiveMapping].color[1][ring][0], mappings[ActiveMapping].color[1][ring][1], mappings[ActiveMapping].color[1][ring][2]};

    for(int i = LEDSPERRING * ring; i < LEDSPERRING * (ring + 1); i ++) {
        if(i < (n + LEDSPERRING * (ring))) {

            // int * color = generateGradient(colorStart, colorEnd, i - LEDSPERRING * ring, LEDSPERRING);
            int r = generateGradient(colorStart[0], colorEnd[0], i - LEDSPERRING * ring, LEDSPERRING );
            int g = generateGradient(colorStart[1], colorEnd[1], i - LEDSPERRING * ring, LEDSPERRING );
            int b = generateGradient(colorStart[2], colorEnd[2], i - LEDSPERRING * ring, LEDSPERRING );


            strip.setPixelColor(i, r, g, b);
            //Serial.println("Setting Pixel " + String(i) + " to " + String(r) + " " + String(g) + " " + String(b));
        }
        else {
            strip.setPixelColor(i, 0, 0, 0);
            //if(DEBUG == TRACE) Serial.println("Setting Pixel " + String(i) + " to " + String(r) + " " + String(g) + " " + String(b));
        }
    }

}


void rainbow(int wait) {
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this loop:
    for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
        // strip.rainbow() can take a single argument (first pixel hue) or
        // optionally a few extras: number of rainbow repetitions (default 1),
        // saturation and value (brightness) (both 0-255, similar to the
        // ColorHSV() function, default 255), and a true/false flag for whether
        // to apply gamma correction to provide 'truer' colors (default true).
        strip.rainbow(firstPixelHue);
        // Above line is equivalent to:
        // strip.rainbow(firstPixelHue, 1, 255, 255, true);
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
    }
}
