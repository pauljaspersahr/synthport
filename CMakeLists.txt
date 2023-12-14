cmake_minimum_required(VERSION 3.14)

project(synthport)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# for keyboard input on mac
find_package(Curses REQUIRED)

# find core audio libs on mac
find_library(CORE_AUDIO_LIB CoreAudio)
find_library(AUDIO_TOOLBOX_LIB AudioToolbox)
find_library(AUDIO_UNIT_LIB AudioUnit)
find_library(CORE_SERVICES_LIB CoreServices)
find_library(CORE_FOUNDATION_LIB CoreFoundation)

# Include configurations for external projects
include(${CMAKE_CURRENT_SOURCE_DIR}/PortAudioConfig.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(synthport main.cpp sine.cpp )

add_subdirectory(model)

# Include headers
target_include_directories(synthport PRIVATE 
  ${PORTAUDIO_DIR}/include
  ${CURSES_INCLUDE_DIR})

# Link libraries 
target_link_libraries(synthport PRIVATE
  portmodel
  ${PORTAUDIO_DIR}/lib/.libs/libportaudio.a
  ${CORE_AUDIO_LIB}
  ${AUDIO_TOOLBOX_LIB}
  ${AUDIO_UNIT_LIB}
  ${CORE_SERVICES_LIB}
  ${CORE_FOUNDATION_LIB}
  ${CURSES_LIBRARIES}
)

# Include test configuration
include(${CMAKE_CURRENT_SOURCE_DIR}/GoogleTestConfig.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tests/SynthportTests.cmake)
