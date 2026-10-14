#include "swissgerman_programmer.h"
#include "sendstring_swiss_de.h" // SEND_STRING types correctly on a Swiss German host
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
    }

    return true;
}
