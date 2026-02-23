target_sources(middleware_tinyusb PRIVATE backend.c)
# EVK board only has one USB port
target_compile_definitions(middleware_tinyusb PUBLIC BOARD_TUD_RHPORT=0)
# QUASAR board supports USB FULL-SPEED
target_compile_definitions(middleware_tinyusb PUBLIC BOARD_TUD_MAX_SPEED=OPT_MODE_FULL_SPEED)
