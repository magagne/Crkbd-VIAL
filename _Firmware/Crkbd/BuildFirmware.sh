#!/bin/bash

set -euo pipefail

# Crkbd VIAL firmware builder
# Builds: crkbd/rev4_1:vial
#
# Native QMK build — no Docker.
# All paths are derived from the script's location.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

QMK_DIR="$REPO_DIR/src/vial-kb/vial-qmk"
FIRMWARE_DIR="$SCRIPT_DIR"

FIRMWARE_NAME="crkbd_rev4_1_vial.uf2"
FIRMWARE_SOURCE="$QMK_DIR/.build/$FIRMWARE_NAME"
ROOT_FIRMWARE="$QMK_DIR/$FIRMWARE_NAME"

BUILD_TARGET="crkbd/rev4_1"
KEYMAP="vial"

printf '\n=== CRKBD VIAL FIRMWARE BUILD ===\n\n'

if ! command -v qmk >/dev/null 2>&1; then
    echo "ERROR: qmk command not found."
    echo "Please install/configure QMK CLI first."
    exit 1
fi

echo "→ QMK is ready."
echo "→ Building $BUILD_TARGET:$KEYMAP..."
echo

rm -f "$FIRMWARE_SOURCE"
rm -f "$ROOT_FIRMWARE"
rm -f "$FIRMWARE_DIR/$FIRMWARE_NAME"

cd "$QMK_DIR"

qmk compile -kb "$BUILD_TARGET" -km "$KEYMAP"

echo
echo "→ Checking firmware output..."

if [[ ! -f "$FIRMWARE_SOURCE" ]]; then
    echo
    echo "ERROR: Build completed but the expected firmware was not found:"
    echo "  $FIRMWARE_SOURCE"
    echo
    echo "Available UF2 files in .build:"
    find "$QMK_DIR/.build" -maxdepth 1 -type f -name '*.uf2' -print 2>/dev/null || true
    exit 1
fi

cp "$FIRMWARE_SOURCE" "$FIRMWARE_DIR/$FIRMWARE_NAME"

# QMK may copy a firmware file into its own root.
# Keep the repository root clean.
rm -f "$ROOT_FIRMWARE"

echo "→ Firmware copied to:"
echo "  $FIRMWARE_DIR/$FIRMWARE_NAME"

echo
echo "=== BUILD COMPLETE ==="
echo

ls -lh "$FIRMWARE_DIR/$FIRMWARE_NAME"
