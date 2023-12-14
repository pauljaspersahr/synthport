
# Define a test executable
add_executable(synthport_tests tests/test.cpp)

# Link the GoogleTest libraries
target_link_libraries(synthport_tests PRIVATE 
    gtest_main
    portmodel)


target_include_directories(synthport_tests PRIVATE 
  ${PORTAUDIO_DIR}/include)

# Register tests with CTest (optional)
add_test(NAME synthport_test COMMAND synthport_tests)
