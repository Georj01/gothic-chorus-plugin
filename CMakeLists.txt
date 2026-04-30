cmake_minimum_required(VERSION 3.20)
project(GothicChorus VERSION 1.0.0)

set(JUCE_DIR "C:/JUCE" CACHE PATH "Path to local JUCE installation")

if(EXISTS "${JUCE_DIR}/CMakeLists.txt")
    add_subdirectory("${JUCE_DIR}" juce)
else()
    include(FetchContent)
    FetchContent_Declare(
        juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.0
    )
    FetchContent_MakeAvailable(juce)
endif()

juce_add_plugin(GothicChorus
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Jurg
    PLUGIN_CODE Gcho
    FORMATS VST3
    PRODUCT_NAME "Gothic Chorus"
)

target_sources(GothicChorus PRIVATE
    src/plugin-processor.cpp
    src/plugin-processor.h
    src/plugin-editor.cpp
    src/plugin-editor.h
)

target_compile_definitions(GothicChorus PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(GothicChorus PRIVATE
    juce::juce_audio_plugin_client
    juce::juce_dsp
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
