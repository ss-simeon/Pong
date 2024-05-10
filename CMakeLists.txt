cmake_minimum_required(VERSION 3.25)
project(PingPong
        VERSION 0.1
        DESCRIPTION "Template for Multi-OS SMFL Build with Visual Studio CMakePresets JSON support"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/Config.h.in src/Config.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(PingPong src/main.cpp)
target_link_libraries(PingPong PRIVATE sfml-graphics)
target_compile_features(PingPong PRIVATE cxx_std_17)

if(WIN32)
    target_link_libraries(PingPong PRIVATE sfml-main)
    set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS")
    target_link_options(PingPong PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

    add_custom_command(
        TARGET PingPong
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PingPong>
        VERBATIM)
endif()

install(TARGETS PingPong)

target_include_directories(PingPong PUBLIC
                           "${CMAKE_CURRENT_BINARY_DIR}/src"
                           )
