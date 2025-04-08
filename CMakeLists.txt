cmake_minimum_required(VERSION 3.10)

# Project name
project(docker_c)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(docker_c main.cpp)

# Link the SQLite library
find_package(SQLite3 REQUIRED)
target_link_libraries(docker_c SQLite::SQLite3)