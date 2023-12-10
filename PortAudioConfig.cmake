include(FetchContent)
include(ExternalProject)

set(PORTAUDIO_DIR ${LIBS_DIR}/portaudio)

# Declare the external project
FetchContent_Declare(
    portaudio
    URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
    SOURCE_DIR ${PORTAUDIO_DIR}
)

# Populate the content
FetchContent_GetProperties(portaudio)
if(NOT portaudio_POPULATED)
    FetchContent_Populate(portaudio)

    # Configure and build portaudio here
    # Note: You may need to adjust these commands based on portaudio's build system
    execute_process(COMMAND ./configure WORKING_DIRECTORY ${PORTAUDIO_DIR})
    execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} -j WORKING_DIRECTORY ${PORTAUDIO_DIR})
endif()
