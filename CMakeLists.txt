cmake_minimum_required(VERSION 3.10)

# Project name
project(docker_c)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main executable
add_executable(docker_c
        main.cpp
        model.cpp
        view.cpp
        controller.cpp
)

# Link the SQLite library
find_package(SQLite3 REQUIRED)
target_link_libraries(docker_c SQLite::SQLite3)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enable testing
enable_testing()

# Add the test executable
add_executable(
        tests
        tests/test_model.cpp
        tests/test_view.cpp
        tests/test_controller.cpp
        model.cpp
        view.cpp
        controller.cpp
)

# Link Google Test and SQLite3 to the test executable
target_link_libraries(tests GTest::GTest GTest::Main SQLite::SQLite3)

# Register the test executable
add_test(NAME AllTests COMMAND tests)

# Ensure the tests target is built when running 'cmake --build .'
add_custom_target(build_and_test ALL
        DEPENDS tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
)