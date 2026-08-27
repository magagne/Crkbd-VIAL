#include "drag_scroll.h"

#include <stdint.h>
#include "raw_hid.h"

static bool drag_scroll_enabled = false;

static void drag_scroll_send(uint8_t command) {
    uint8_t data[32] = {0};
    data[0] = command;
    raw_hid_send(data, sizeof(data));
}

void drag_scroll_init(void) {
    drag_scroll_enabled = false;
}

void drag_scroll_set(bool enabled) {
    if (drag_scroll_enabled == enabled) {
        return;
    }

    drag_scroll_enabled = enabled;

    if (enabled) {
        drag_scroll_send(0x53);
    } else {
        drag_scroll_send(0x73);
    }
}

void drag_scroll_task(void) {
}