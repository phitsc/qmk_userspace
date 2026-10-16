#pragma once

#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h" // CH_ keycodes for the Swiss German host layout

enum custom_keycodes {
    VRSN = SAFE_RANGE, // print version
    CIRC,              // ^
    GRV_TLD,           // ` or ~
    BREATHE,           // switch the RGB / LED matrix to the breathing effect
    USER_SAFE_RANGE    // first free keycode for keymap-specific keycodes
};

// Ctrl+Shift+Space, bound to the PowerToys Command Palette. A combination any keyboard
// can type, so the same shortcut also works on a laptop keyboard.
#define LAUNCHER C(S(KC_SPC))

// True if the key at row/col does something on the given (active) layer, or holds an active
// layer. Used to light only the meaningful keys while a Fn layer is held.
bool key_active_on_layer(uint8_t layer, uint8_t row, uint8_t col);

// Optional per-keymap hook, called before the userspace keycodes are handled.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
