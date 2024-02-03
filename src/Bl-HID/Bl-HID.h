//
// Created by Paul on 03/02/2024.
//

#ifndef REMOTE4_PIO_REWRITE_BL_HID_H
#define REMOTE4_PIO_REWRITE_BL_HID_H

#include <BleKeyboard.h>

extern BleKeyboard bleKeyboard;

void setupBleHID();

void sendEncoders(int mapping, int encoder, int encoderValue, bool ModifierPressed);


#endif //REMOTE4_PIO_REWRITE_BL_HID_H
