//
// Created by Paul on 03/02/2024.
//

#include "Bl-HID.h"
#include "Mappings.h"
#include "Arduino.h"
#include "../Encoder/Encoder.h"


BleKeyboard bleKeyboard; // Define the bleKeyboard object

void setupBleHID() {
    bleKeyboard.begin();

}


void sendEncoders(int mapping, int encoder, int encoderValue, bool ModifierPressed) {


    if(encoderValue == 0) return;
    bool sign = encoderValue < 0;
    keyCombo combo = mappings[mapping].combos[encoder][sign];// Send all variables over Serial
    Serial.println("------------------");
    Serial.print("Mapping: ");
    Serial.println(mapping);
    Serial.print("Encoder: ");
    Serial.println(encoder);
    Serial.print("Encoder Value: ");
    Serial.println(encoderValue);
    Serial.println("Redued to:");
    Serial.print(encoderValue/2);
    Serial.print("Sign: ");
    Serial.println(sign);
    Serial.print("Keys: ");
    for (int i = 0; i < 4; i++) {
        Serial.print(combo.keys[i]);
        Serial.print(" ");
    }

    //make encoder value positive
    if(encoderValue < 0) encoderValue = -encoderValue;
    encoderValue = encoderValue/2;
    if(encoderValue == 0) return;


    if(true) {//keyComboType == 0) {
        for (int i = 0; i < 4; i++) {
            if (combo.keys[i] == 0) {
                Serial.println("Sequence ended.");
                break;
            }
            bleKeyboard.press(combo.keys[i]);
            Serial.print("Pressed: ");
            Serial.println(combo.keys[i]);
        }
        bleKeyboard.releaseAll();



    for (int i = 0; i < encoderValue; i++) {
        if(ModifierPressed) {
            bleKeyboard.press(combo.modifier);
            Serial.print("Modifier Pressed: ");
            Serial.println(combo.modifier);
        }

        for (int i = 0; i < 4; i++) {
            if (combo.secondaryKeys[i] == 0) {
                Serial.println("Secondary Sequence ended.");
                break;
            }
            bleKeyboard.press(combo.secondaryKeys[i]);
            Serial.print("Pressed: ");
            Serial.println(combo.secondaryKeys[i]);
        }

        bleKeyboard.releaseAll();
    }

    } else {
        // TODO
    }
}
