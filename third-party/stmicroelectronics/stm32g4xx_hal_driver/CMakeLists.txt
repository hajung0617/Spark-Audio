add_library(stm32g4xx_hal_driver "")

add_subdirectory(stm32g4xx_hal_config)

target_link_libraries(stm32g4xx_hal_driver PRIVATE cmsis_device_g4)

target_sources(stm32g4xx_hal_driver
    PRIVATE
        src/Src/stm32g4xx_hal.c
        src/Src/stm32g4xx_hal_adc.c
        src/Src/stm32g4xx_hal_adc_ex.c
        #src/Src/stm32g4xx_hal_comp.c
        #src/Src/stm32g4xx_hal_cordic.c
        src/Src/stm32g4xx_hal_cortex.c
        #src/Src/stm32g4xx_hal_crc.c
        #src/Src/stm32g4xx_hal_crc_ex.c
        #src/Src/stm32g4xx_hal_cryp.c
        #src/Src/stm32g4xx_hal_cryp_ex.c
        #src/Src/stm32g4xx_hal_dac.c
        #src/Src/stm32g4xx_hal_dac_ex.c
        src/Src/stm32g4xx_hal_dma.c
        #src/Src/stm32g4xx_hal_dma_ex.c
        src/Src/stm32g4xx_hal_exti.c
        #src/Src/stm32g4xx_hal_fdcan.c
        src/Src/stm32g4xx_hal_flash.c
        src/Src/stm32g4xx_hal_flash_ex.c
        src/Src/stm32g4xx_hal_flash_ramfunc.c
        #src/Src/stm32g4xx_hal_fmac.c
        src/Src/stm32g4xx_hal_gpio.c
        #src/Src/stm32g4xx_hal_hrtim.c
        src/Src/stm32g4xx_hal_i2c.c
        src/Src/stm32g4xx_hal_i2c_ex.c
        #src/Src/stm32g4xx_hal_i2s.c
        #src/Src/stm32g4xx_hal_irda.c
        #src/Src/stm32g4xx_hal_iwdg.c
        #src/Src/stm32g4xx_hal_lptim.c
        #src/Src/stm32g4xx_hal_msp_template.c
        #src/Src/stm32g4xx_hal_nand.c
        #src/Src/stm32g4xx_hal_nor.c
        #src/Src/stm32g4xx_hal_opamp.c
        #src/Src/stm32g4xx_hal_opamp_ex.c
        src/Src/stm32g4xx_hal_pcd.c
        src/Src/stm32g4xx_hal_pcd_ex.c
        src/Src/stm32g4xx_hal_pwr.c
        src/Src/stm32g4xx_hal_pwr_ex.c
        #src/Src/stm32g4xx_hal_qspi.c
        src/Src/stm32g4xx_hal_rcc.c
        src/Src/stm32g4xx_hal_rcc_ex.c
        #src/Src/stm32g4xx_hal_rng.c
        #src/Src/stm32g4xx_hal_rtc.c
        #src/Src/stm32g4xx_hal_rtc_ex.c
        src/Src/stm32g4xx_hal_sai.c
        #src/Src/stm32g4xx_hal_sai_ex.c
        #src/Src/stm32g4xx_hal_smartcard.c
        #src/Src/stm32g4xx_hal_smartcard_ex.c
        #src/Src/stm32g4xx_hal_smbus.c
        src/Src/stm32g4xx_hal_spi.c
        #src/Src/stm32g4xx_hal_spi_ex.c
        #src/Src/stm32g4xx_hal_sram.c
        src/Src/stm32g4xx_hal_tim.c
        src/Src/stm32g4xx_hal_tim_ex.c
        #src/Src/stm32g4xx_hal_timebase_tim_template.c
        src/Src/stm32g4xx_hal_uart.c
        src/Src/stm32g4xx_hal_uart_ex.c
        #src/Src/stm32g4xx_hal_usart.c
        #src/Src/stm32g4xx_hal_usart_ex.c
        #src/Src/stm32g4xx_hal_wwdg.c
        #src/Src/stm32g4xx_ll_adc.c
        #src/Src/stm32g4xx_ll_comp.c
        #src/Src/stm32g4xx_ll_cordic.c
        #src/Src/stm32g4xx_ll_crc.c
        #src/Src/stm32g4xx_ll_crs.c
        #src/Src/stm32g4xx_ll_dac.c
        #src/Src/stm32g4xx_ll_dma.c
        #src/Src/stm32g4xx_ll_exti.c
        #src/Src/stm32g4xx_ll_fmac.c
        #src/Src/stm32g4xx_ll_fmc.c
        #src/Src/stm32g4xx_ll_gpio.c
        #src/Src/stm32g4xx_ll_hrtim.c
        #src/Src/stm32g4xx_ll_i2c.c
        #src/Src/stm32g4xx_ll_lptim.c
        #src/Src/stm32g4xx_ll_lpuart.c
        #src/Src/stm32g4xx_ll_opamp.c
        #src/Src/stm32g4xx_ll_pwr.c
        #src/Src/stm32g4xx_ll_rcc.c
        #src/Src/stm32g4xx_ll_rng.c
        #src/Src/stm32g4xx_ll_rtc.c
        #src/Src/stm32g4xx_ll_spi.c
        #src/Src/stm32g4xx_ll_tim.c
        #src/Src/stm32g4xx_ll_ucpd.c
        #src/Src/stm32g4xx_ll_usart.c
        src/Src/stm32g4xx_ll_usb.c
        #src/Src/stm32g4xx_ll_utils.c
)

target_include_directories(stm32g4xx_hal_driver PUBLIC src/Inc)

target_compile_definitions(stm32g4xx_hal_driver PUBLIC USE_FULL_LL_DRIVER)
