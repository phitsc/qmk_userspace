#pragma once

#include QMK_KEYBOARD_H

/* CH KEYS (host OS layout: Swiss German)

    degree      KC_GRAVE
    question    KC_MINUS
    caret       KC_EQUAL
    lessThan    KC_NONUS_BACKSLASH
    ü           KC_LEFT_BRACKET
    exclamation KC_RIGHT_BRACKET
    ö           KC_SEMICOLON
    ä           KC_QUOTE
    dollar      KC_NONUS_HASH
    comma       KC_COMMA
    period      KC_DOT
    dash        KC_SLASH

*/

enum custom_keycodes {
    VRSN = SAFE_RANGE, // print version
    CIRC,              // ^
    GRV_TLD,           // ` or ~
    BRK_Z,             // Break followed by Z
    USER_SAFE_RANGE    // first free keycode for keymap-specific keycodes
};

// Optional per-keymap hook, called before the userspace keycodes are handled.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
