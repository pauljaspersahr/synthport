include(FetchContent)
include(ExternalProject)

set(PORTAUDIO_DIR ${LIBS_DIR}/portaudio)
set(PORTAUDIO_LIB_PATH "${PORTAUDIO_DIR}/lib/.libs/libportaudio.a") 

if(EXISTS ${PORTAUDIO_LIB_PATH})
    message(STATUS "PortAudio library found: ${PORTAUDIO_LIB_PATH}")
else()
    message(STATUS "PortAudio library not found. Fetching and building.")

    FetchContent_Declare(
        portaudio
        URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
        SOURCE_DIR ${PORTAUDIO_DIR}
    )

    FetchContent_Populate(portaudio)

    execute_process(COMMAND ./configure WORKING_DIRECTORY ${PORTAUDIO_DIR})
    execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -j WORKING_DIRECTORY ${PORTAUDIO_DIR})
endif()
