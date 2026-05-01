# Gothic Chorus Plugin (VST3)

A minimalist VST3 audio plugin designed to generate dense, dark, and stereo spatial modulations. This project emulates the characteristic "dreamy" guitar tone of 90s gothic metal (style of *Type O Negative* on albums like *October Rust*), prioritizing Digital Signal Processing (DSP) quality over redundant graphical interfaces.

Developed in **C++** using the **JUCE** framework and **CMake**.

## Architecture and Philosophy

This project follows a strict design philosophy: **one tool, a single responsibility**.
*   **DSP Engine:** Utilizes `juce::dsp::Chorus` to guarantee industrial-grade performance and prevent CPU bottlenecks.
*   **State Management:** Implements `juce::AudioProcessorValueTreeState` (APVTS) to bridge the audio logic with the user interface, enabling full DAW automation and data persistence (preset save/load).
*   **UI:** Purely functional rotary controls. Zero visual noise.

## Controls (APVTS Parameters)

1.  **Rate:** Controls the Low-Frequency Oscillator (LFO) from `0.1 Hz` to `10.0 Hz`. Defines the speed of the modulation.
2.  **Depth:** Adjusts the detuning intensity from `0.0` to `1.0`.
3.  **Mix:** Dry/Wet balance (`0.0` to `1.0`). For the optimal dense tone, a setting above 50% is highly recommended.

## Build Requirements

The build system is centrally managed via CMake, ensuring cross-platform compatibility without cluttering the repository with temporary files or local environment binaries.

*   **CMake** (v3.15 or higher)
*   **C++ Compiler** with C++20 support (MSVC, Clang, or GCC)
*   *JUCE Note:* The `CMakeLists.txt` is configured to search for the JUCE framework locally at `C:/JUCE`. If not found, it will automatically fallback to `FetchContent` to dynamically download version 8.0.0 from GitHub during the configuration step.

## Build Instructions

Open your terminal at the root of the repository and execute the following commands sequentially:
```bash
# 1. Generate the build files (Automatically creates the build/ directory)
cmake -B build

# 2. Compile the plugin in Release mode for maximum performance
cmake --build build --config Release
