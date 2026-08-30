#include QMK_KEYBOARD_H

#include "modules/drag_scroll/drag_scroll.h"


/* ---------------------------------------------------------------------------
 * Custom keycodes
 * ------------------------------------------------------------------------- */

enum custom_keycodes {

    HID_DragScroll = QK_KB_0,
    ALT_CLK,
    GUI_CLK,
    SHIFT_CLK,
    CTRL_CLK,
    LED_DragScroll,
};


/* ---------------------------------------------------------------------------
 * Modified mouse click helper
 * ------------------------------------------------------------------------- */

static void send_modified_click(uint8_t modifier) {

    register_code(modifier);
    tap_code(KC_BTN1);
    unregister_code(modifier);

}


/* ---------------------------------------------------------------------------
 * Custom keycode processing
 * ------------------------------------------------------------------------- */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case HID_DragScroll:

            drag_scroll_set(record->event.pressed);
            return false;


        case LED_DragScroll:

            if (record->event.pressed) {
                register_code(KC_SCRL);
            } else {
                unregister_code(KC_SCRL);
            }

            return false;


        case ALT_CLK:

            if (record->event.pressed) {
                send_modified_click(KC_LALT);
            }

            return false;


        case GUI_CLK:

            if (record->event.pressed) {
                send_modified_click(KC_LGUI);
            }

            return false;


        case SHIFT_CLK:

            if (record->event.pressed) {
                send_modified_click(KC_LSFT);
            }

            return false;


        case CTRL_CLK:

            if (record->event.pressed) {
                send_modified_click(KC_LCTL);
            }

            return false;

    }

    return true;
}


/* ---------------------------------------------------------------------------
 * Drag-scroll initialization and task
 * ------------------------------------------------------------------------- */

void keyboard_post_init_user(void) {

    drag_scroll_init();

}


void housekeeping_task_user(void) {

    drag_scroll_task();

}


/* ===========================================================================
 * KEYMAP
 *
 * The actual user layout is managed by Vial.
 *
 * This source keymap is intentionally minimal and contains only KC_NO.
 * It exists only to satisfy QMK's required keymap definition.
 *
 * ---------------------------------------------------------------------------
 *
 * Corne physical layout:
 *
 *       LEFT HAND                              RIGHT HAND
 *
 *   ┌────┬────┬────┬────┬────┬────┐      ┌────┬────┬────┬────┬────┬────┐
 *   │ NO │ NO │ NO │ NO │ NO │ NO │      │ NO │ NO │ NO │ NO │ NO │ NO │
 *   ├────┼────┼────┼────┼────┼────┤      ├────┼────┼────┼────┼────┼────┤
 *   │ NO │ NO │ NO │ NO │ NO │ NO │      │ NO │ NO │ NO │ NO │ NO │ NO │
 *   ├────┼────┼────┼────┼────┼────┤      ├────┼────┼────┼────┼────┼────┤
 *   │ NO │ NO │ NO │ NO │ NO │ NO │      │ NO │ NO │ NO │ NO │ NO │ NO │
 *   └────┴────┴────┴────┴────┴────┘      └────┴────┴────┴────┴────┴────┘
 *
 *                 ┌────┬────┬────┐  ┌────┬────┬────┐
 *                 │ NO │ NO │ NO │  │ NO │ NO │ NO │
 *                 └────┴────┴────┘  └────┴────┴────┘
 *
 * =========================================================================== */


#ifdef LAYOUT_split_3x6_3_ex2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x6_3_ex2(

        /* Row 0 — LEFT: 7 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 0 — RIGHT: 7 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* Row 1 — LEFT: 7 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 1 — RIGHT: 7 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* Row 2 — LEFT: 6 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 2 — RIGHT: 6 keys */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* LEFT THUMB: 3 keys */
        KC_NO, KC_NO, KC_NO,

        /* RIGHT THUMB: 3 keys */
        KC_NO, KC_NO, KC_NO

    )

};


#else

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x6_3(

        /* Row 0 — LEFT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 0 — RIGHT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* Row 1 — LEFT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 1 — RIGHT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* Row 2 — LEFT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        /* Row 2 — RIGHT */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,


        /* LEFT THUMB: 3 keys */
        KC_NO, KC_NO, KC_NO,

        /* RIGHT THUMB: 3 keys */
        KC_NO, KC_NO, KC_NO

    )

};


#endif


/* ===========================================================================
 * ENCODER MAP
 *
 * Minimal fallback only.
 * The actual Vial layout/configuration remains external.
 * =========================================================================== */

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

    [0] = {
        ENCODER_CCW_CW(KC_NO, KC_NO),
        ENCODER_CCW_CW(KC_NO, KC_NO),
        ENCODER_CCW_CW(KC_NO, KC_NO),
        ENCODER_CCW_CW(KC_NO, KC_NO),
    },

};


#endif
