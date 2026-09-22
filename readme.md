# Crkbd-VIAL

Custom VIAL firmware for the Corne Rev4.1.

## Overview

This repository contains a VIAL-enabled QMK firmware build for the Corne Rev4.1.

The project deliberately separates firmware functionality from the keyboard layout:

- QMK provides the firmware and custom functionality.
- VIAL provides the complete user keyboard layout.
- The `.vil` file is the authoritative layout configuration.
- `keymap.c` contains firmware logic and only a minimal fallback layout.

The complete user layout is therefore maintained in VIAL and is not duplicated in the QMK source.

## Firmware target

    crkbd/rev4_1:vial

## Repository structure

    Firmware/Crkbd/
    ├── BuildFirmware.sh
    └── crkbd_rev4_1_vial.uf2

    src/vial-qmk/keyboards/crkbd/keymaps/vial/
    ├── keymap.c
    ├── rules.mk
    └── modules/
        ├── drag_scroll/
        │   ├── drag_scroll.c
        │   └── drag_scroll.h
        ├── auto_mouse_layer/
        │   ├── auto_mouse_layer.c
        │   └── auto_mouse_layer.h
        └── tap_dance/
            ├── tap_dance.c
            └── tap_dance.h

The custom firmware modules are kept with the VIAL keymap so their implementation and integration points remain together.

## Building

The recommended build method is the project build script.

From the repository root:

    ./Firmware/Crkbd/BuildFirmware.sh

The script builds:

    crkbd/rev4_1:vial

The generated firmware is:

    Firmware/Crkbd/crkbd_rev4_1_vial.uf2

## Manual build

The firmware can also be built directly from the bundled QMK source.

From the repository root:

    cd src/vial-qmk
    make crkbd/rev4_1:vial

The ARM GNU toolchain must be available in the system PATH.

No developer-specific filesystem path is required.

## Flashing

After building, flash:

    Firmware/Crkbd/crkbd_rev4_1_vial.uf2

to the Corne Rev4.1 using the normal RP2040 UF2 bootloader procedure.

After flashing, open VIAL and load the desired `.vil` configuration.

## VIAL layout

The complete keyboard layout is configured through VIAL.

The `.vil` configuration is the source of truth for:

- Layer assignments
- Key assignments
- Tap Dance assignments
- VIAL configuration

The full user layout should not be recreated in `keymap.c`.

This separation prevents the firmware source and VIAL configuration from becoming two competing sources of truth.

## Custom firmware functionality

The firmware provides:

- HID Auto Mouse Layer
- Drag scrolling
- Scroll Lock HID control for DragScroll
- Modified mouse clicks
- QMK mouse keys
- RGB controls
- Encoder support
- Custom firmware keycodes

The custom firmware modules are located at:

    src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/

## HID Auto Mouse Layer

HID Auto Mouse Layer automatically enables the mouse layer when the Ploopy Nano-2 reports trackball activity.

The feature has two host paths.

### macOS

On macOS, the Ploopy Nano-2 sends an Auto Mouse Layer activity packet through Raw HID.

The packet uses:

    Byte 0: 0x41
    Byte 1: 0x01

The QMK firmware receives this packet through `raw_hid_receive_kb()` and activates the macOS mouse layer.

For the current layout:

    Base layer 0
    Mouse layer 3
    Timeout 450 ms

The normal 450 ms timeout applies to this Raw HID/macOS path.

### Windows

On Windows, Auto Mouse Layer uses the Caps Lock LED state as the state signal.

The Ploopy Nano-2 sends a Caps Lock press/release through the host:

    Trackball movement starts  → Caps Lock ON
    Trackball remains moving   → no repeated Caps Lock traffic
    400 ms without movement    → Caps Lock OFF

Windows reports the resulting Caps Lock LED state back to the keyboard.

The QMK firmware then maps that state to the Windows mouse layer:

    Caps Lock ON  → Windows mouse layer ON
    Caps Lock OFF → Windows mouse layer OFF

For the current layout:

    Base layer 4
    Mouse layer 7

The Windows path is state-based and does not use the 450 ms QMK Auto Mouse timeout.

### Layer separation

The two Auto Mouse paths intentionally use different signaling mechanisms:

    macOS   → Raw HID activity → layer 3 → 450 ms timeout
    Windows → Caps Lock state  → layer 7 → LED state controls layer

The Windows path is only active while the Windows base layer (layer 4) is selected.

Changing away from the relevant base layer disables the corresponding Auto Mouse state.

## DragScroll

DragScroll is implemented as a separate module:

    src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/drag_scroll/

The module provides:

    drag_scroll_init()
    drag_scroll_set()
    drag_scroll_task()

The custom keycodes are:

    HID_DragScroll
    LED_DragScroll

`HID_DragScroll` controls the DragScroll HID transport.

`LED_DragScroll` sends a Scroll Lock toggle to the host. Scroll Lock is reserved for DragScroll state and is not used by HID Auto Mouse Layer.

The DragScroll implementation is independent of the Auto Mouse Layer implementation.

## Tap Dance

Tap Dance is implemented as a separate module:

    src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/tap_dance/

The module provides:

    td_accent_init()

The current implementation configures Vial Tap Dance entry 0.

### Accent Tap Dance

Tap Dance entry 0 provides two behaviors:

    Tap   → [
    Hold  → {

The hold action is implemented as:

    LSFT(KC_LBRC)

Double-tap and tap-hold actions are not configured.

The entry uses the default QMK tapping term.

The Tap Dance entry is initialized during keyboard startup by:

    td_accent_init()

The physical key assignment uses:

    TD(0)

The assignment is present on the symbol layers where the Accent Tap Dance is required.

The Tap Dance implementation is independent of DragScroll and HID Auto Mouse Layer.

## Custom keycodes

The firmware currently defines:

    HID_DragScroll
    LED_DragScroll

These keycodes implement firmware functionality.

Their assignment to physical keys is performed through VIAL.

## Tap Dance

Tap Dance assignments are configured through VIAL.

They are not maintained as a duplicate full keyboard layout in `keymap.c`.

To restore the configured Tap Dance assignments, load the appropriate `.vil` configuration in VIAL.

## Source of truth

Firmware functionality belongs in:

    src/vial-qmk/

The user keyboard layout belongs in:

    .vil

The minimal fallback layout in `keymap.c` exists only because QMK requires a keymap definition for compilation and introspection.

It is not intended to represent the user's actual keyboard configuration.

## Development workflow

For a firmware change:

    ./Firmware/Crkbd/BuildFirmware.sh

Then:

1. Flash the generated `.uf2`.
2. Open VIAL.
3. Load the desired `.vil` configuration.
4. Verify the layout.
5. Test the firmware functionality.

When changing a custom firmware module, keep its header and source together under:

    src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/

## Hardware

Target hardware:

    Corne Rev4.1

QMK/VIAL target:

    crkbd/rev4_1:vial

## Build script

The project build entry point is:

    Firmware/Crkbd/BuildFirmware.sh

The script uses repository-relative paths and does not depend on a developer-specific filesystem location.
