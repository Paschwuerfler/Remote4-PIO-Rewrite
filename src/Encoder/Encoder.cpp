//
// Created by Paul on 26/01/2024.
//

#include "Encoder.h"


#include <Arduino.h>
#include "../Bl-HID/Bl-HID.h"

#define decoderInterrupt 27

rotaryDecoder decoder = rotaryDecoder(0x38);

int encoderPins[4] = {R0B, R1B, R2B, R3B};

volatile bool flag = false;


int OldEncoderValues[4] = {0,0,0,0};

void moved()
{
    // one should not read the PPCF8574 in the interrupt routine.
    flag = true;

}

void setupEncoder() {
    pinMode(decoderInterrupt, INPUT_PULLUP);
    attachInterrupt(decoderInterrupt, moved, FALLING);

    pinMode(R0B, INPUT_PULLUP);
    pinMode(R1B, INPUT_PULLUP);
    pinMode(R2B, INPUT_PULLUP);
    pinMode(R3B, INPUT_PULLUP);
    pinMode(WLEDB, OUTPUT);

    flag = false;

    Wire.begin();
    Wire.setClock(100000);
    decoder.begin(4);
    decoder.readInitialState();

}


void getEncoderValueArray() {
    for (int i = 0; i < 4; i++)
    {
        EncoderValues[i] = decoder.getValue(i);
    }
}

void updateEncoderDifferences() {

    for (int i = 0; i < 4; i++)
    {
        encoderDifferences[i] = decoder.getValue(i) - EncoderValues[i];
        EncoderValues[i] = decoder.getValue(i);
    }

}

bool encoderTick() {
    if (flag) {
        decoder.update();
        flag = false;
        return true;
    }
    return false;
}


void updateBLEEncoders() {
    //Serial.println("Updating BLE Encoders");

    getEncoderValueArray();
    for (int i = 0; i < 4; i++)
    {
        if(encoderDifferences[i] != 0) {
            bool ModifierPressed = false;
            if(digitalRead(encoderPins[i]) == LOW) bool ModifierPressed = true;


            sendEncoders(0, i, (EncoderValues[i] - OldEncoderValues[i]), ModifierPressed);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        OldEncoderValues[i] = EncoderValues[i];
    }

}