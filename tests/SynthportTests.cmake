
# Define a test executable
add_executable(synthport_tests test.cpp)

# Link the GoogleTest libraries
target_link_libraries(synthport_tests PRIVATE gtest_main)

# Include directories if necessary
# target_include_directories(synthport_tests PRIVATE ../include)

# Register tests with CTest (optional)
add_test(NAME synthport_test COMMAND synthport_tests)
