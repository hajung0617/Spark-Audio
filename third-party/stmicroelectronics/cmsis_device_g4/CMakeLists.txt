add_library(cmsis_device_g4 "")

set_target_properties(cmsis_device_g4 PROPERTIES LINKER_LANGUAGE C)

if(HARDWARE STREQUAL EVK)
    set(STM32G4_MCU_MODEL STM32G473xx CACHE INTERNAL "STM32G4 MCU model Define for CMSIS-Device library")
endif()

set(CMSIS_G4_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

target_sources(cmsis_device_g4
    PUBLIC
        ${CMSIS_G4_PATH}/Include/stm32g4xx.h
        ${CMSIS_G4_PATH}/Include/system_stm32g4xx.h
)

target_link_libraries(cmsis_device_g4 PUBLIC cmsis_5)
target_compile_definitions(cmsis_device_g4 PUBLIC ${STM32G4_MCU_MODEL} USE_HAL_DRIVER)
target_include_directories(cmsis_device_g4 PUBLIC ${CMSIS_G4_PATH}/Include)
