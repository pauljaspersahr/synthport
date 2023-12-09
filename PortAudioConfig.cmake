
include(FetchContent)
include(ExternalProject)

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
