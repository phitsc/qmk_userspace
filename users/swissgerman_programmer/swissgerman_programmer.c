#include "swissgerman_programmer.h"
#include "version.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    switch (keycode)
    {
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
        break;

        case CIRC:
            if (record->event.pressed) {
                SEND_STRING("= "); // ^
            }
        break;

        case GRV_TLD:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    clear_mods();
                    SEND_STRING(SS_DOWN(X_RALT) "=" SS_UP(X_RALT) " ");
                } else {
                    SEND_STRING(SS_DOWN(X_LSFT) "=" SS_UP(X_LSFT) " ");
                }
            }
        break;

        case BRK_Z:
            if (record->event.pressed) {
                tap_code(KC_BRK);
                SEND_STRING("Y");
            }
        break;
    }

    return true;
}
