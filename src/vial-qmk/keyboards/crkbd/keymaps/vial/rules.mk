VIA_ENABLE          = yes
VIAL_ENABLE         = yes
RAW_ENABLE          = yes

LTO_ENABLE          = yes
RGBLIGHT_ENABLE     = yes
RGB_MATRIX_ENABLE   = no
MOUSEKEY_ENABLE     = yes
OLED_ENABLE         = no
OLED_DRIVER         = SSD1306
EXTRAKEY_ENABLE     = no
COMBO_ENABLE        = no
QMK_SETTINGS       = no
ENCODER_MAP_ENABLE = yes

SRC += modules/drag_scroll/drag_scroll.c
