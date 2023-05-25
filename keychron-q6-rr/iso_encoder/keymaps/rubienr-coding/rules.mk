ENCODER_MAP_ENABLE = yes

BOOTMAGIC_ENABLE   = yes # press ESC during boot for DFU mode
CONSOLE_ENABLE     = yes # for debugging: qmk console
TERMINAL_ENABLE    = yes # command-line-like interface thorugh a text ditor

NKRO_ENABLE        = no  # USB Nkey Rollover
CAPS_WORD_ENABLE   = yes # caps lock -> caps word

# for umlaut and caps lock
COMBO_ENABLE       = yes # umlaut
# TAP_DANCE_ENABLE   = yes # caps lock

# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE        = no # USB Nkey Rollover

# unicode and special characters. only one at the same time: UNICODE, UNICODEMAP, UCIS
#UNICODE_ENABLE    = no  # https://docs.qmk.fm/#/feature_unicode?id=basic-unicode
#UNICODEMAP_ENABLE = no  # https://docs.qmk.fm/#/feature_unicode?id=unicode-map
UCIS_ENABLE        = yes # https://docs.qmk.fm/#/feature_unicode?id=ucis
