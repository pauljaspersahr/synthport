cmake_minimum_required(VERSION 3.14)

project(synthport)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS)

include(FetchContent)
include(ExternalProject)

set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(PORTAUDIO_DIR ${LIBS_DIR}/portaudio)

FetchContent_Declare(
  portaudio
  URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
  SOURCE_DIR ${PORTAUDIO_DIR}
)

FetchContent_GetProperties(portaudio)
if(NOT portaudio_POPULATED)
  FetchContent_Populate(portaudio)

  ExternalProject_Add(
    portaudio_ext
    SOURCE_DIR ${PORTAUDIO_DIR}
    CONFIGURE_COMMAND ${PORTAUDIO_DIR}/configure
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j
    BUILD_IN_SOURCE TRUE
    INSTALL_COMMAND ""
  )
endif()

add_executable(synthport main.cpp sine.cpp)

target_include_directories(synthport PRIVATE ${PORTAUDIO_DIR}/include)
target_link_libraries(synthport PRIVATE ${PORTAUDIO_DIR}/lib/.libs/libportaudio.a)

find_library(CORE_AUDIO_LIB CoreAudio)
find_library(AUDIO_TOOLBOX_LIB AudioToolbox)
find_library(AUDIO_UNIT_LIB AudioUnit)
find_library(CORE_SERVICES_LIB CoreServices)
find_library(CORE_FOUNDATION_LIB CoreFoundation)

target_link_libraries(synthport PRIVATE
  ${CORE_AUDIO_LIB}
  ${AUDIO_TOOLBOX_LIB}
  ${AUDIO_UNIT_LIB}
  ${CORE_SERVICES_LIB}
  ${CORE_FOUNDATION_LIB}
)
