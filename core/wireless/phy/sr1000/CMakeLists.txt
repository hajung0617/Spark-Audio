target_sources(swc
    PRIVATE
        sr_calib.c
        sr_nvm.c
        sr_nvm_private.c
        sr_spectral.c
    PUBLIC
        sr_def.h
        sr_access.h
        sr_calib.h
        sr_nvm.h
        sr_nvm_private.h
        sr_pwr_up.h
        sr_reg.h
        sr_spectral.h
        sr_utils.h
        sr1000_def.h
        sr1020_V8_3_reg.h
)

target_include_directories(swc PUBLIC ${CMAKE_CURRENT_LIST_DIR})
