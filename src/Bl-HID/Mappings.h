//
// Created by Paul on 03/02/2024.
//

#ifndef REMOTE4_PIO_REWRITE_MAPPINGS_H
#define REMOTE4_PIO_REWRITE_MAPPINGS_H

#include "BleKeyboard.h"

struct keyCombo {
    uint8_t keys[4];
    uint8_t secondaryKeys[4];
    uint8_t modifier;
    // media keys
    MediaKeyReport media;
};

struct Map {
    int color[4][2][3];
    keyCombo combos[4][2];
};

static int ActiveMapping = 0;
#define definedPresets 1


static Map mappings[] = {
        {
                .color = {
                        {{255, 0, 0}, {0, 255, 0}},
                        {{0, 255, 0}, {0, 0, 255}},
                        {{0, 0, 255}, {255, 0, 0}},
                        {{0, 0, 0}, {120, 120, 120}}
                },
                .combos = {
                        {
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'p', 0}, .secondaryKeys = {KEY_LEFT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT},
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'p', 0}, .secondaryKeys = {KEY_RIGHT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT}
                        },
                        {
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'k', 0}, .secondaryKeys = {KEY_LEFT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT},
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'k', 0}, .secondaryKeys = {KEY_RIGHT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT}
                        },
                        {
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'j', 0}, .secondaryKeys = {KEY_LEFT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT},
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'j', 0}, .secondaryKeys = {KEY_RIGHT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT}
                        },
                        {
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'u', 0}, .secondaryKeys = {KEY_LEFT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT},
                                {.keys = {KEY_LEFT_ALT, KEY_LEFT_CTRL, 'u', 0}, .secondaryKeys = {KEY_RIGHT_ARROW, 0, 0, 0}, .modifier = KEY_LEFT_SHIFT}
                        }
                }
        }
};

#endif //REMOTE4_PIO_REWRITE_MAPPINGS_H
