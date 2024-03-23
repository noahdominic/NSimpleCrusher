cmake_minimum_required(VERSION 3.14.0)

option(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES "Enable VST 3 Plug-in Examples" OFF)
option(SMTG_ENABLE_VST3_HOSTING_EXAMPLES "Enable VST 3 Hosting Examples" OFF)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/Program Files/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(NSimpleCrusher
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "NSimpleCrusher VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(NSimpleCrusher
    source/version.h
    source/NSimpleCrushercids.h
    source/NSimpleCrusherprocessor.h
    source/NSimpleCrusherprocessor.cpp
    source/NSimpleCrushercontroller.h
    source/NSimpleCrushercontroller.cpp
    source/NSimpleCrusherentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(NSimpleCrusher
        PRIVATE
            resource/NSimpleCrushereditor.uidesc
    )
    target_link_libraries(NSimpleCrusher
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(NSimpleCrusher
        RESOURCES
            "resource/NSimpleCrushereditor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (NSimpleCrusher
    RESOURCES
        resource/7BC0FB63A6BB5AEA85F013219101B41E_snapshot.png
        resource/7BC0FB63A6BB5AEA85F013219101B41E_snapshot_2.0x.png
)

target_link_libraries(NSimpleCrusher
    PRIVATE
        sdk
)

smtg_target_configure_version_file(NSimpleCrusher)

if(SMTG_MAC)
    smtg_target_set_bundle(NSimpleCrusher
        BUNDLE_IDENTIFIER com.noahdominic.NSimpleCrusher
        COMPANY_NAME "Noah Dominic Miranda Silvio"
    )
    smtg_target_set_debug_executable(NSimpleCrusher
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(NSimpleCrusher PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT NSimpleCrusher)

        smtg_target_set_debug_executable(NSimpleCrusher
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
