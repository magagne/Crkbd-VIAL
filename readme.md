# Crkbd VIAL

VIAL firmware configuration for the **Corne rev4.1**.

This repository contains the VIAL keymap and custom firmware components for the `crkbd/rev4_1` target.

## Firmware Build

The firmware is built natively on macOS using the QMK Make build system and the Arm GNU Toolchain.

**Docker is not required.**

The repository includes a dedicated build script:

```text
Firmware/Crkbd/BuildFirmware.sh
```

### Build the firmware

From any directory, execute:

```bash
/Users/matthieu/Documents/GitHub/Crkbd-VIAL/Firmware/Crkbd/BuildFirmware.sh
```

The script:

1. Locates the repository and the bundled `vial-qmk` source tree automatically.
2. Uses the Arm GNU Toolchain 15.3 installed at:

   ```text
   /Applications/ArmGNUToolchain/15.3.rel1/arm-none-eabi/bin
   ```
3. Builds:

   ```text
   crkbd/rev4_1:vial
   ```
4. Creates:

   ```text
   crkbd_rev4_1_vial.uf2
   ```
5. Copies the resulting firmware to:

   ```text
   Firmware/Crkbd/crkbd_rev4_1_vial.uf2
   ```

### Important

Do **not** use:

```bash
qmk compile -kb crkbd/rev4_1 -km vial
```

The QMK CLI installed on this system does not expose the `compile` subcommand.

The build script uses the native QMK Make system instead:

```bash
cd /Users/matthieu/Documents/GitHub/Crkbd-VIAL/src/vial-qmk
PATH="/Applications/ArmGNUToolchain/15.3.rel1/arm-none-eabi/bin:$PATH" make crkbd/rev4_1:vial
```

You normally do **not** need to execute this command manually. Use `BuildFirmware.sh`.

## Firmware Output

After a successful build:

```text
Firmware/Crkbd/crkbd_rev4_1_vial.uf2
```

This is the UF2 firmware file to flash to the Corne rev4.1.

## Repository Structure

```text
Crkbd-VIAL/
├── Firmware/
│   └── Crkbd/
│       ├── BuildFirmware.sh
│       └── crkbd_rev4_1_vial.uf2
├── src/
│   └── vial-qmk/
│       └── ...
└── README.md
```

## Build Environment

* **Keyboard:** Corne rev4.1
* **Firmware:** VIAL
* **Build system:** QMK Make
* **Target:** `crkbd/rev4_1:vial`
* **Compiler:** Arm GNU Toolchain 15.3.1
* **Platform:** macOS
* **Docker:** Not required

