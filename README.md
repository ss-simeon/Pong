![Windows/Linux/MacOS Compilation Status](https://github.com/ss-simeon/ping-pong/actions/workflows/os-cross-compilation.yml/badge.svg)

# CMake SFML Project Template

This SFML Project Template is a modified version of [cmake-sfml-project](https://github.com/SFML/cmake-sfml-project). It is meant as an internal template for new projects.

On top of the functionalities of the base template, it provides the following functionalities:
* Makes MAJOR and MINOR versions available in the source code under [Config.h.in](src/Config.h.in).
* Defines CMake configuration and build presents for Visual Studio ease-of-use under [CMakePresets.json](CMakePresets.json).
* Sets entry point to `/SUBSYSTEM:WINDOWS` to allow Visual Studio based compilation without entering into a Command Prompt.
