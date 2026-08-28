# Crkbd VIAL Firmware

VIAL firmware for the **Corne (Crkbd) Rev4.1**.

This repository contains a self-contained VIAL-QMK source tree, the
Corne Rev4.1 VIAL configuration, the custom drag-scroll module, and
the build script used to produce the firmware.

## Supported firmware

- Keyboard: `crkbd/rev4_1`
- Keymap: `vial`
- Firmware: `crkbd_rev4_1_vial.uf2`

This repository is intentionally focused on the Corne VIAL firmware.
Legacy VIA, LSKBD, and other keyboard-specific material is not included.

## Repository structure

```text
Crkbd-VIAL/
├── Firmware/
│   └── Crkbd/
│       ├── BuildFirmware.sh
│       └── crkbd_rev4_1_vial.uf2
│
└── src/
    └── vial-qmk/
        └── keyboards/
            └── crkbd/
                ├── rev4_1/
                └── keymaps/
                    └── vial/
                        └── modules/
                            └── drag_scroll/
