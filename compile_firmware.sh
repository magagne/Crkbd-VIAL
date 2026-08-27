#!/bin/bash

set -e

QMK_DIR="/Users/matthieu/Documents/GitHub/Crkbd-VIAL/src/vial-kb/vial-qmk"
FIRMWARE_DIR="/Users/matthieu/Documents/GitHub/Crkbd-VIAL/firmware"
FIRMWARE="crkbd_rev4_1_vial.uf2"

echo "=== QMK FIRMWARE BUILD ==="

cd "$QMK_DIR"

echo "→ Compiling $FIRMWARE..."

docker run --rm -it \
  -w /qmk_firmware \
  -v "$QMK_DIR:/qmk_firmware" \
  -e SKIP_GIT=1 \
  ghcr.io/qmk/qmk_cli \
  sh -c 'qmk compile -kb crkbd/rev4_1 -km vial'

echo "→ Moving firmware..."

mv "$QMK_DIR/$FIRMWARE" "$FIRMWARE_DIR/$FIRMWARE"

echo
echo "=== BUILD COMPLETE ==="
echo
echo "Firmware:"
echo "$FIRMWARE_DIR/$FIRMWARE"
echo
ls -lh "$FIRMWARE_DIR/$FIRMWARE"
