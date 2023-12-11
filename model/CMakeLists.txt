add_library(portmodel PortAudioContext.cpp)

target_include_directories(portmodel PRIVATE 
  ${PORTAUDIO_DIR}/include
  )

target_link_libraries(portmodel PRIVATE
  ${PORTAUDIO_DIR}/lib/.libs/libportaudio.a
  )