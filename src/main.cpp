//
// Created by Paul on 26/01/2024.
//

#include "main.h"
#include "Arduino.h"
#include "Display/Display.h"
#include "Encoder/Encoder.h"
#include "LEDs/LEDs.h"
#include "Bl-HID/Bl-HID.h"

unsigned int encoderUpdateTime = 0;
unsigned int MaxEncoderUpdateTime = 0;

unsigned int bluetoothUpdateTime = 0;
unsigned int MaxBluetoothUpdateTime = 0;

unsigned int drawUpdateTime = 0;
unsigned int oldDrawUpdateTime = 0;

unsigned int displayUpdateTime = 0;

unsigned int LEDUpdateTime = 0;

int loops = 0;
int lastloopupdate = 0;
float lastloopFrequency = 0;

unsigned int oldLoopTime = 0;
unsigned int loopTime = 0;

bool encoderUpdateOccured = false;

float loopTimeAverage = 0;


void printStats() {

    drawUpdateTime = micros();

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);


    display.println("Stats:");

    display.print("EUT:\t"); display.print(encoderUpdateTime);  display.print("MEUT:\t"); display.println(MaxEncoderUpdateTime);
    //display.print("LF:\t"); display.println(1.0/(oldLoopTime*0.000001));
    display.print("LF:\t"); display.println(lastloopFrequency);

    display.print("DRT:"); display.print(oldDrawUpdateTime); display.print("LUT:"); display.println(LEDUpdateTime);
    display.print("DIT:\t"); display.println(displayUpdateTime);

    display.print("BUT:\t"); display.print(bluetoothUpdateTime); display.print("MBUT:\t"); display.println(MaxBluetoothUpdateTime);

    //print all encoder values using Decoder.getValue()


    for (int i = 0; i < 4; i++)
    {
        display.print(decoder.getValue(i));
        display.print(" | ");
    }



    oldDrawUpdateTime = micros() - drawUpdateTime;


    displayUpdateTime = micros();
    display.display();
    displayUpdateTime = micros() - displayUpdateTime;




}


void setup() {
    setupStrip();
    setupDisplay();
    setupEncoder();
    setupBleHID();
    rainbow(15);



    Serial.begin(115200);
    Serial.println("Hello, world!");

}


void loop() {
    loopTime = micros();




    encoderUpdateTime = micros();
    encoderUpdateOccured = encoderTick();
    encoderUpdateTime = micros() - encoderUpdateTime;
    if (encoderUpdateTime > 10) MaxEncoderUpdateTime = encoderUpdateTime;

    if(encoderUpdateOccured) {updateEncoderDifferences();}



    if(millis() % 100 == 0) printStats();

    if(encoderUpdateOccured) {updateEncoderDifferences();}


    LEDUpdateTime = micros();
    for(int i = 0; i < 4; i++) {
        //setRing(i, decoder.getValue(i) / 10, 0, 34, 234);
        setRingfromMapping(i, decoder.getValue(i) / 10);
    }
    strip.show();
    LEDUpdateTime = micros() - LEDUpdateTime;

    if(encoderUpdateOccured) {updateEncoderDifferences();}

    bluetoothUpdateTime = micros();

    if(bleKeyboard.isConnected()) {
        //if(millis() % 50 == 0)
            updateBLEEncoders();
    }

    bluetoothUpdateTime = micros() - bluetoothUpdateTime;
    if(bluetoothUpdateTime > 10) MaxBluetoothUpdateTime = bluetoothUpdateTime;



    oldLoopTime = micros() - loopTime;

    loops ++;

    if(millis()- lastloopupdate > 1000) {
        lastloopFrequency = loops / ((millis() - lastloopupdate) * 0.001);
        loops = 0;
        lastloopupdate = millis();
    }



}
