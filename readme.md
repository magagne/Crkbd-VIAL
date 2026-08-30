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

    src/vial-qmk/
    ├── keyboards/crkbd/keymaps/vial/
    │   ├── keymap.c
    │   └── rules.mk
    └── modules/drag_scroll/

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

- Drag scrolling
- Scroll-lock HID control
- Modified mouse clicks
- QMK mouse keys
- RGB controls
- Encoder support
- Custom firmware keycodes

The custom drag-scroll module is located at:

    src/vial-qmk/modules/drag_scroll/

## Custom keycodes

The firmware defines:

    HID_DragScroll
    LED_DragScroll
    ALT_CLK
    GUI_CLK
    SHIFT_CLK
    CTRL_CLK

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

## Hardware

Target hardware:

    Corne Rev4.1

QMK/VIAL target:

    crkbd/rev4_1:vial

## Build script

The project build entry point is:

    Firmware/Crkbd/BuildFirmware.sh

The script uses repository-relative paths and does not depend on a developer-specific filesystem location.
