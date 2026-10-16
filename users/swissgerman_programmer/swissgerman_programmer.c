#include "swissgerman_programmer.h"
#include "sendstring_swiss_de.h" // SEND_STRING types correctly on a Swiss German host
#include "version.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
    return true;
}

bool key_active_on_layer(uint8_t layer, uint8_t row, uint8_t col)
{
    // The key's effective keycode: the first non-transparent one from the top active layer down
    for (int8_t l = layer; l >= 0; l--) {
        if (l > 0 && !layer_state_is(l)) { // the Basic layer is the default layer, not in layer_state
            continue;
        }
        const uint16_t keycode = keymap_key_to_keycode(l, (keypos_t){ .row = row, .col = col });
        if (keycode == KC_TRNS) {
            continue;
        }
        const bool held_fn_key = IS_QK_MOMENTARY(keycode) && layer_state_is(QK_MOMENTARY_GET_LAYER(keycode));
        return (l == layer && keycode != KC_NO) || held_fn_key;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode)
    {
        case VRSN:
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;

        case CIRC:
            SEND_STRING("^"); // dead key, SEND_STRING adds the space
            return false;

        case GRV_TLD:
            if (get_mods() & MOD_MASK_SHIFT) {
                const uint8_t mods = get_mods();
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING("~");
                set_mods(mods);
            } else {
                SEND_STRING("`");
            }
            return false;

        case BREATHE:
#if defined(RGB_MATRIX_ENABLE) && defined(ENABLE_RGB_MATRIX_BREATHING)
            rgb_matrix_mode(RGB_MATRIX_BREATHING);
#elif defined(LED_MATRIX_ENABLE) && defined(ENABLE_LED_MATRIX_BREATHING)
            led_matrix_mode(LED_MATRIX_BREATHING);
#endif
            return false;
    }

    return true;
}
