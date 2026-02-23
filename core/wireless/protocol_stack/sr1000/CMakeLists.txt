target_sources(swc
    PRIVATE
        wps_phy_common.c
    PUBLIC
        wps_phy_def.h
)

target_include_directories(swc PUBLIC ${CMAKE_CURRENT_LIST_DIR})
