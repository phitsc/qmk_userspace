#include "swissgerman_programmer.h"
#include <string.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ` ~   |   1  |   2  |   3  |   4  |   5  |  F2  |           |  F4  |   6  |   7  |   8  |   9  |   0  |   '    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  F3  |           |  F5  |   Z  |   U  |   I  |   O  |   P  |   Ü    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Fn1   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------| F11  |           | F12  |------+------+------+------+------+--------|
 * |  Shift |   Y  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  Up  |   -    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Fn3 |      |  Fn2 | Alt  |CtlEsc|                                       |CtlEsc|  Fn1 | Left | Down |Right |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |C+S+Es|      |       | PrtSc|Shift |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | CS+O |      |      |
 *                                 |Backsp| Del  |------|       |------|Enter |Space |
 *                                 |      |      | Ctrl |       | CS+M |      |      |
 *                                 `--------------------'       `--------------------'
 */
[0] = LAYOUT_ergodox(
    // left hand
    GRV_TLD , CH_1        , CH_2   , CH_3    , CH_4           , CH_5   , KC_F2   ,
    KC_TAB  , CH_Q        , CH_W   , CH_E    , CH_R           , CH_T   , KC_F3   ,
    MO(1)   , CH_A        , CH_S   , CH_D    , CH_F           , CH_G   ,
    KC_LSFT , CH_Y        , CH_X   , CH_C    , CH_V           , CH_B   , KC_F11  ,
    MO(3)   , _______     , MO(2)  , KC_LALT , LCTL_T(KC_ESC) ,
                                                                C(S(KC_ESC)) , _______ ,
                                                                         _______ ,
                                                     KC_BSPC  , KC_DEL , KC_LCTL ,
    // right hand
    KC_F4   , CH_6   , CH_7    , CH_8    , CH_9     , CH_0    , CH_QUOT  ,
    KC_F5   , CH_Z   , CH_U    , CH_I    , CH_O     , CH_P    , CH_UDIA  ,
              CH_H   , CH_J    , CH_K    , CH_L     , CH_ODIA , CH_ADIA  ,
    KC_F12  , CH_N   , CH_M    , CH_COMM , CH_DOT   , KC_UP   , CH_MINS  ,
              RCTL_T(KC_ESC)   , MO(1)   , KC_LEFT  , KC_DOWN , KC_RIGHT ,
    KC_PSCR , KC_RSFT ,
    C(S(CH_O)),
    C(S(CH_M)), KC_ENT  , KC_SPC
),
/* Symbol layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    §   |   ¦  |   @  |   #  |      |      |      |           |      |      |   \  |      |      |   !  |    ^   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   =  |   €  |      |      |      |           |      |      |   [  |   ]  |      |      |    ¨   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   +  |   -  |   *  |   /  |   %  |------|           |------|   |  |   {  |   }  |   &  |   ^  |    $   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   -  |   <  |   >  |   :  | PgUp |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      | Home | PgDn | End  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |Space |Enter |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[1] = LAYOUT_ergodox(
    // left hand
    CH_SECT , CH_BRKP , CH_AT   , CH_HASH , _______ , _______ , _______ ,
    _______ , CH_EXLM , CH_EQL  , CH_EURO , _______ , _______ , _______ ,
    _______ , CH_PLUS , CH_MINS , CH_ASTR , CH_SLSH , CH_PERC ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,
                                                      _______ , _______ ,
                                                                _______ ,
                                            KC_SPC  , KC_ENT  , _______ ,
    // right hand
    _______ , _______ , CH_BSLS , _______ , _______ , CH_EXLM , CH_CIRC ,
    _______ , _______ , CH_LBRC , CH_RBRC , _______ , _______ , CH_DIAE ,
              CH_PIPE , CH_LCBR , CH_RCBR , CH_AMPR , CIRC    , CH_DLR  ,
    _______ , CH_MINS , CH_LABK , CH_RABK , CH_COLN , KC_PGUP , _______ ,
                        _______ , _______ , KC_HOME , KC_PGDN , KC_END  ,
    _______ , _______ ,
    _______ ,
    _______ , _______ , _______
),
/* Function layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | BL Tog |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  BL ↑  |  F4  |  F5  |  F6  |      |      |      |           |      |      |      |      |      | PrtSc|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  BL ↓  |  F7  |  F8  |  F9  |      |      |------|           |------|      | Vol- | Vol+ |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F10 |  F11 |  F12 |      | Brth |      |           |      |      | Mute |      |  MB1 |  MUp |  MB2   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      | MLeft| MDown| MRght|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Mode-| Mode+|       | Prev | Next |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Vol+ |      |      |
 *                                 | Prev | Next |------|       |------| Mute | Play |
 *                                 |      |      |      |       | Vol- |      |      |
 *                                 `--------------------'       `--------------------'
 */
[2] = LAYOUT_ergodox(
        // left hand
        LM_TOGG , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , _______ ,
        LM_BRIU , KC_F4   , KC_F5   , KC_F6   , _______ , _______ , _______ ,
        LM_BRID , KC_F7   , KC_F8   , KC_F9   , _______ , _______ ,
        _______ , KC_F10  , KC_F11  , KC_F12  , _______ , BREATHE , _______ ,
        _______ , _______ , _______ , _______ , _______ ,
                                                          LM_PREV , LM_NEXT ,
                                                                    _______ ,
                                                KC_MPRV , KC_MNXT , _______ ,
        // right hand
        _______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
        _______ , _______ , _______ , _______ , _______ , KC_PSCR , _______ ,
                  _______ , KC_VOLD , KC_VOLU , _______ , _______ , _______ ,
        _______ , _______ , KC_MUTE , _______ , MS_BTN1 , MS_UP   , MS_BTN2 ,
                            _______ , _______ , MS_LEFT , MS_DOWN , MS_RGHT ,
        KC_MPRV , KC_MNXT ,
        KC_VOLU ,
        KC_VOLD , KC_MUTE , KC_MPLY
    ),
/* Misc layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Reset  |      |      | Gui+E| Gui+R|      |      |           |      |      |      | Gui+I|      |      | Reset  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Vrsn  | Gui+A|      | Gui+D|      |      |------|           |------|      |      |      | Gui+L|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      | Gui+C| Gui+V|      |      |           |      | Gui+N| Gui+M|      |      | Gui+↑|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |  F13 |                                       |      |      | Gui+←| Gui+↓| Gui+→|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | F14  |      |------|       |------| F15  |Launch|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[3] = LAYOUT_ergodox(
        // left hand
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,
        QK_BOOT , _______ , _______ , G(CH_E) , G(CH_R) , _______ , _______ ,
        VRSN    , G(CH_A) , _______ , G(CH_D) , _______ , _______ ,
        _______ , _______ , _______ , G(CH_C) , G(CH_V) , _______ , _______ ,
        _______ , _______ , _______ , _______ , KC_F13  ,
                                                          _______ , _______ ,
                                                                    _______ ,
                                                KC_F14  , _______ , _______ ,
        // right hand
        KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11     , KC_F12     , _______ ,
        _______ , _______ , _______ , G(CH_I) , _______    , _______    , QK_BOOT ,
                  _______ , _______ , _______ , G(CH_L)    , _______    , _______ ,
        _______ , G(CH_N) , G(CH_M) , _______ , _______    , G(KC_UP)   , _______ ,
                            _______ , _______ , G(KC_LEFT) , G(KC_DOWN) , G(KC_RIGHT) ,
        _______ , _______ ,
        _______ ,
        _______ , KC_F15  , LAUNCHER
    ),
};

// Show the active layer on the three right-hand LEDs (original ErgoDox / ErgoDox EZ).
// On the Infinity these functions do nothing.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(state))
    {
        case 1:
            ergodox_right_led_2_on();
        break;

        case 2:
            ergodox_right_led_3_on();
        break;

        case 3:
            ergodox_right_led_1_on();
        break;
    }

    return state;
}

#ifdef LED_MATRIX_ENABLE
// ErgoDox Infinity (single-colour key LEDs): while a Fn layer is held, keep only the keys that
// do something on it (plus the held Fn keys) lit and switch the others off.
// Each half only drives its own LEDs, hence the per-half led_min/led_max range.
bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t layer = get_highest_layer(layer_state);
    if (layer == 0) {
        return false;
    }

    const uint8_t val = led_matrix_get_val();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led >= led_min && led < led_max) {
                led_matrix_set_value(led, key_active_on_layer(layer, row, col) ? val : 0);
            }
        }
    }
    return false;
}
#endif

#ifdef ST7565_ENABLE
#include ST7565_FONT_H // the driver's 6x8 font, to draw the layer name at twice its size

// Ergodox Infinity LCD: show the layer name in large letters with the active modifiers above it,
// and tint the backlight per layer in the cheat sheet colours (Symbol green, Function blue, Misc orange).
static void set_lcd_rgb(uint8_t r, uint8_t g, uint8_t b) {
    ergodox_infinity_lcd_color(r * 257u, g * 257u, b * 257u);
}

// Draw a character of the 6x8 font at twice the size (12x16 pixels) with its top left corner at x/y.
static void write_char_2x(uint8_t x, uint8_t y, char c) {
    for (uint8_t col = 0; col < ST7565_FONT_WIDTH; col++) {
        const uint8_t bits = pgm_read_byte(&font[((uint8_t)c - ST7565_FONT_START) * ST7565_FONT_WIDTH + col]);
        for (uint8_t row = 0; row < ST7565_FONT_HEIGHT; row++) {
            if (bits & (1 << row)) {
                st7565_write_pixel(x + 2 * col,     y + 2 * row,     true);
                st7565_write_pixel(x + 2 * col + 1, y + 2 * row,     true);
                st7565_write_pixel(x + 2 * col,     y + 2 * row + 1, true);
                st7565_write_pixel(x + 2 * col + 1, y + 2 * row + 1, true);
            }
        }
    }
}

// Draw a string at twice the size, centred horizontally, in the lower 3/4 of the display.
static void write_centered_2x(const char *text) {
    const uint8_t width = strlen(text) * 2 * ST7565_FONT_WIDTH;
    uint8_t       x     = (ST7565_DISPLAY_WIDTH - width) / 2;
    for (; *text; text++, x += 2 * ST7565_FONT_WIDTH) {
        write_char_2x(x, ST7565_FONT_HEIGHT + 2, *text);
    }
}

void st7565_task_user(void) {
    const char *name = "";

    if (layer_state_is(3)) {
        name = "Misc";
        set_lcd_rgb(255, 126, 0);  // orange
    }
    else if (layer_state_is(2)) {
        name = "Function";
        set_lcd_rgb(0, 108, 255);  // blue
    }
    else if (layer_state_is(1)) {
        name = "Symbol";
        set_lcd_rgb(0, 255, 102);  // green
    }
    else {
        set_lcd_rgb(0, 0, 0);      // off
    }

    char    status[4] = "   ";
    uint8_t mods      = get_mods();

    if (mods & MOD_MASK_SHIFT) {
        status[0] = 'S';
    }

    if (mods & MOD_BIT(KC_LALT)) {
        status[1] = 'A';
    }

    if (mods & MOD_MASK_CTRL) {
        status[2] = 'C';
    }

    st7565_clear();
    st7565_set_cursor(0, 0);
    st7565_write(status, false);
    write_centered_2x(name);
}
#endif
