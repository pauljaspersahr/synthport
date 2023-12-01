cmake_minimum_required(VERSION 3.14)

project(synthport)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS)


include(FetchContent)
include(ExternalProject)

# Define the desired directories
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(PORTAUDIO_DIR ${LIBS_DIR}/portaudio)

FetchContent_Declare(
  portaudio
  URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
  # Optionally, you can include a URL_HASH for security
  # URL_HASH SHA256=<hash_value>
  SOURCE_DIR ${PORTAUDIO_DIR}
)


FetchContent_GetProperties(portaudio)
if(NOT portaudio_POPULATED)
  FetchContent_Populate(portaudio)

  # The portaudio directory is now created, and the archive is extracted there

  # Define the build and install steps
  ExternalProject_Add(
    portaudio_ext
    SOURCE_DIR ${PORTAUDIO_DIR}
    CONFIGURE_COMMAND ${PORTAUDIO_DIR}/configure
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j
    BUILD_IN_SOURCE TRUE
    INSTALL_COMMAND ""
    # Optionally, define install commands if needed
  )
endif()

# Assuming you have your executable
add_executable(synthport main.cpp)

target_include_directories(synthport PRIVATE ${PORTAUDIO_DIR}/include)
target_link_libraries(synthport PRIVATE ${PORTAUDIO_DIR}/lib/.libs/libportaudio.a)

