#pragma once

#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h" // CH_ keycodes for the Swiss German host layout

enum custom_keycodes {
    VRSN = SAFE_RANGE, // print version
    CIRC,              // ^
    GRV_TLD,           // ` or ~
    USER_SAFE_RANGE    // first free keycode for keymap-specific keycodes
};

// Win+F16, bound to the PowerToys Command Palette (it does not accept F13-F24 alone)
#define LAUNCHER G(KC_F16)

// Optional per-keymap hook, called before the userspace keycodes are handled.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
