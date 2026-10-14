#include "swissgerman_programmer.h"

// Original Drop ALT (ATSAMD51). Only buildable with QMK 0.26.x, see README.

enum alt_keycodes {
    LED_AREA = USER_SAFE_RANGE // cycle lit LEDs: keys + edge, keys only, edge only
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Basic layer
 * ,-----------------------------------------------------------------------------------------------.
 * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  '  |  ^  |  Backsp   | Del |
 * |-----------------------------------------------------------------------------------------------|
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  Ü  |  ¨  |   $    | Home|
 * |-----------------------------------------------------------------------------------------------|
 * | Fn1      |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ä  |   Enter    | PgUp|
 * |-----------------------------------------------------------------------------------------------|
 * | Shift       |  Y  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  -  |  Shift  | Up  | PgDn|
 * |-----------------------------------------------------------------------------------------------|
 * |CtlEsc| Fn3  | Alt  |                Space                | Fn1  | Fn2  |    | Left| Down|Right|
 * `-----------------------------------------------------------------------------------------------'
 */
[0] = LAYOUT_65_ansi_blocker(
    GRV_TLD,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
    KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NUHS, KC_HOME,
    MO(1),          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
    LCTL_T(KC_ESC), MO(3),   KC_LALT,                           KC_SPC,                             MO(1),   MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
),

/* Symbol layer
 * ,-----------------------------------------------------------------------------------------------.
 * |  §  |  ¦  |  @  |  #  |     |     |     |  \  |     |     |  !  |  ^  |     |    Del    |     |
 * |-----------------------------------------------------------------------------------------------|
 * |        |  !  |  =  |  €  |     |     |     |  [  |  ]  |     |     |  ¨  |     |        | End |
 * |-----------------------------------------------------------------------------------------------|
 * |          |  +  |  -  |  *  |  /  |  %  |  |  |  {  |  }  |  &  |  ^  |  $  |            |     |
 * |-----------------------------------------------------------------------------------------------|
 * |             |     |     |     |     |     |  -  |  <  |  >  |  :  |     |         | PgUp|     |
 * |-----------------------------------------------------------------------------------------------|
 * |      |      |      |                                     |      |      |    | Home| PgDn| End |
 * `-----------------------------------------------------------------------------------------------'
 */
[1] = LAYOUT_65_ansi_blocker(
    KC_GRV,  RALT(KC_1), RALT(KC_2), RALT(KC_3), _______, _______, _______,    RALT(KC_NUBS), _______,       _______,   S(KC_RBRC), KC_EQL,  _______, KC_DEL,  _______,
    _______, S(KC_RBRC), S(KC_0),    RALT(KC_E), _______, _______, _______,    RALT(KC_LBRC), RALT(KC_RBRC), _______,   _______,    KC_RBRC, _______, _______, KC_END,
    _______, S(KC_1),    KC_SLSH,    S(KC_3),    S(KC_7), S(KC_5), RALT(KC_7), RALT(KC_QUOT), RALT(KC_NUHS), S(KC_6),   CIRC,       KC_NUHS,          _______, _______,
    _______, _______,    _______,    _______,    _______, _______, KC_SLSH,    KC_NUBS,       S(KC_NUBS),    S(KC_DOT), _______,    _______,          KC_PGUP, _______,
    _______, _______,    _______,                                  _______,                                             _______,    _______, KC_HOME, KC_PGDN, KC_END
),

/* Function layer
 * Based on Drop's default Fn keys. Hold Fn2, then the right Fn1 key, for the misc layer.
 * ,-----------------------------------------------------------------------------------------------.
 * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |   Prev    | Next|
 * |-----------------------------------------------------------------------------------------------|
 * | Brth   | Spd-| Val+| Spd+| Hue+| Sat+|     |     |     |     |PrtSc|ScrLk|Pause|        |     |
 * |-----------------------------------------------------------------------------------------------|
 * |          |Mode-| Val-|Mode+| Hue-| Sat-|     | Vol-| Vol+|     |     |     |            |     |
 * |-----------------------------------------------------------------------------------------------|
 * |             | Area|RGBTg|     |     |     | NKRO| Mute|     |     |     |   MB1   | MUp | MB2 |
 * |-----------------------------------------------------------------------------------------------|
 * |      |      |      |                Play                 | Fn3  |      |    |MLeft|MDown|MRght|
 * `-----------------------------------------------------------------------------------------------'
 */
[2] = LAYOUT_65_ansi_blocker(
    _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MPRV, KC_MNXT,
    RGB_M_B, RGB_SPD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,
    _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, KC_VOLD, KC_VOLU, _______, _______, _______,          _______, _______,
    _______, LED_AREA, RGB_TOG, _______, _______, _______, NK_TOGG, KC_MUTE, _______, _______, _______, MS_BTN1,          MS_UP,   MS_BTN2,
    _______, _______,  _______,                            KC_MPLY,                            MO(3),   _______, MS_LEFT, MS_DOWN, MS_RGHT
),

/* Misc layer
 * ,-----------------------------------------------------------------------------------------------.
 * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |           |     |
 * |-----------------------------------------------------------------------------------------------|
 * | Reset  |     |     |Gui+E|Gui+R|     |     |     |Gui+I|     |     |     |     |        |     |
 * |-----------------------------------------------------------------------------------------------|
 * | Vrsn     |Gui+A|     |Gui+D|     |     |     |     |     |Gui+L|     |     |            |     |
 * |-----------------------------------------------------------------------------------------------|
 * |             |     |     |Gui+C|Gui+V|     |     |Brk,Z|     |     |     |         |Gui+↑|     |
 * |-----------------------------------------------------------------------------------------------|
 * |Ctrl+¨|      |      |               CA+Spc                |Gui+M |      |    |Gui+←|Gui+↓|Gui+→|
 * `-----------------------------------------------------------------------------------------------'
 */
[3] = LAYOUT_65_ansi_blocker(
    _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______,
    QK_BOOT,    _______, _______, G(KC_E), G(KC_R), _______, _______, _______, G(KC_I), _______, _______, _______, _______, _______,    _______,
    VRSN,       G(KC_A), _______, G(KC_D), _______, _______, _______, _______, _______, G(KC_L), _______, _______,          _______,    _______,
    _______,    _______, _______, G(KC_C), G(KC_V), _______, _______, BRK_Z,   _______, _______, _______, _______,          G(KC_UP),   _______,
    C(KC_RBRC), _______, _______,                            LCA(KC_SPC),                        G(KC_M), _______, G(KC_LEFT), G(KC_DOWN), G(KC_RIGHT)
),

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_AREA:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR):
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        break;
                }
                rgb_matrix_set_color_all(0, 0, 0);
            }
            return false;
    }

    return true;
}
