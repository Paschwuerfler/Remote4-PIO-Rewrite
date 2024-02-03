//
// Created by Paul on 26/01/2024.
//

#ifndef REMOTE4_PIO_REWRITE_ENCODER_H
#define REMOTE4_PIO_REWRITE_ENCODER_H

#include "rotaryDecoder.h"


#define decoderInterrupt 27

#define R0B 4
#define R1B 0
#define R2B 23
#define R3B 26
#define WLEDB 17



extern rotaryDecoder decoder;


void setupEncoder();

static int EncoderValues[4] = {0,0,0,0};

static int encoderDifferences[4] = {0,0,0,0};

bool encoderTick();

void updateEncoderDifferences();

void updateBLEEncoders();


#endif //REMOTE4_PIO_REWRITE_ENCODER_H
