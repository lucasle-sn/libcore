cmake_minimum_required(VERSION 3.6)
project(libcore)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(libcore_DOXYGEN_BUILD_ENABLED "Enable Doxygen Build" OFF)

message(STATUS "Enable testing")
enable_testing()

find_package(fmt REQUIRED)
find_package(Threads REQUIRED)

# Add third-party libraries
option(libcore_ENABLE_TESTS "Enable libcore tests" OFF)
if(libcore_ENABLE_TESTS)
  add_subdirectory(third_party/gtest)
endif()

add_subdirectory(public_types)
add_subdirectory(utilities)

# Doxygen setup
if (libcore_DOXYGEN_BUILD_ENABLED)
  message(STATUS "Doxygen build enabled")
  add_subdirectory(doxygen)
else()
  message(STATUS "Doxygen build disabled")
endif()
