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
 * | Alt  | Fn3  |CtlEsc|                Space                | Fn1  | Fn2  |    | Left| Down|Right|
 * `-----------------------------------------------------------------------------------------------'
 */
[0] = LAYOUT_65_ansi_blocker(
    GRV_TLD,        CH_1,    CH_2,    CH_3,    CH_4,    CH_5,    CH_6,    CH_7,    CH_8,    CH_9,    CH_0,    CH_QUOT, CH_CIRC, KC_BSPC, KC_DEL,
    KC_TAB,         CH_Q,    CH_W,    CH_E,    CH_R,    CH_T,    CH_Z,    CH_U,    CH_I,    CH_O,    CH_P,    CH_UDIA, CH_DIAE, CH_DLR,  KC_HOME,
    MO(1),          CH_A,    CH_S,    CH_D,    CH_F,    CH_G,    CH_H,    CH_J,    CH_K,    CH_L,    CH_ODIA, CH_ADIA,          KC_ENT,  KC_PGUP,
    KC_LSFT,        CH_Y,    CH_X,    CH_C,    CH_V,    CH_B,    CH_N,    CH_M,    CH_COMM, CH_DOT,  CH_MINS, KC_RSFT,          KC_UP,   KC_PGDN,
    KC_LALT,        MO(3),   LCTL_T(KC_ESC),                    KC_SPC,                             MO(1),   MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
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
    CH_SECT, CH_BRKP, CH_AT,   CH_HASH, _______, _______, _______, CH_BSLS, _______, _______, CH_EXLM, CH_CIRC, _______, KC_DEL,  _______,
    _______, CH_EXLM, CH_EQL,  CH_EURO, _______, _______, _______, CH_LBRC, CH_RBRC, _______, _______, CH_DIAE, _______, _______, KC_END,
    _______, CH_PLUS, CH_MINS, CH_ASTR, CH_SLSH, CH_PERC, CH_PIPE, CH_LCBR, CH_RCBR, CH_AMPR, CIRC,    CH_DLR,           _______, _______,
    _______, _______, _______, _______, _______, _______, CH_MINS, CH_LABK, CH_RABK, CH_COLN, _______, _______,          KC_PGUP, _______,
    _______, _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END
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
 * |             |     |     |Gui+C|Gui+V|     |     |Gui+M|     |     |     |         |Gui+↑|     |
 * |-----------------------------------------------------------------------------------------------|
 * |      |      |Ctrl+¨|               CA+Spc                |      |      |    |Gui+←|Gui+↓|Gui+→|
 * `-----------------------------------------------------------------------------------------------'
 */
[3] = LAYOUT_65_ansi_blocker(
    _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______,
    QK_BOOT,    _______, _______, G(CH_E), G(CH_R), _______, _______, _______, G(CH_I), _______, _______, _______, _______, _______,    _______,
    VRSN,       G(CH_A), _______, G(CH_D), _______, _______, _______, _______, _______, G(CH_L), _______, _______,          _______,    _______,
    _______,    _______, _______, G(CH_C), G(CH_V), _______, _______, G(CH_M), _______, _______, _______, _______,          G(KC_UP),   _______,
    _______,    _______, C(CH_DIAE),                         LCA(KC_SPC),                        _______, _______, G(KC_LEFT), G(KC_DOWN), G(KC_RIGHT)
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

// Hue per layer, same colours as the cheat sheets: Symbol green, Function blue, Misc orange.
static const uint8_t layer_hues[] = { [1] = 102, [2] = 152, [3] = 21 };

// While a Fn layer is active, light the keys that do something on it in the layer's colour
// (plus the held Fn keys) and switch the other keys off. The edge keeps its colour.
// On the Basic layer the effect runs as usual.
bool rgb_matrix_indicators_user(void) {
    const uint8_t layer = get_highest_layer(layer_state);

    if (layer == 0 || layer >= sizeof(layer_hues)) {
        // LEDs excluded by LED_AREA are not redrawn by the effect, so clear any layer colours left on them
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            if (!HAS_ANY_FLAGS(g_led_config.flags[i], rgb_matrix_get_flags())) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
        return false;
    }

    const HSV hsv = { layer_hues[layer], 255, rgb_matrix_get_val() };
    const RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED) {
                continue;
            }

            // The key's effective keycode: the first non-transparent one from the top active layer down
            bool lit = false;
            for (int8_t l = layer; l >= 0; l--) {
                if (l > 0 && !layer_state_is(l)) { // the Basic layer is the default layer, not in layer_state
                    continue;
                }
                const uint16_t keycode = keymap_key_to_keycode(l, (keypos_t){ .row = row, .col = col });
                if (keycode == KC_TRNS) {
                    continue;
                }
                const bool held_fn_key = IS_QK_MOMENTARY(keycode) && layer_state_is(QK_MOMENTARY_GET_LAYER(keycode));
                lit = (l == layer && keycode != KC_NO) || held_fn_key;
                break;
            }

            if (lit) {
                rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
            } else {
                rgb_matrix_set_color(led, 0, 0, 0);
            }
        }
    }

    return false;
}
