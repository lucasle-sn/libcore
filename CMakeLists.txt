cmake_minimum_required(VERSION 3.6)
project(libcore)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(libcore_DOXYGEN_BUILD_ENABLED "Enable libcore doxygen build" OFF)
option(libcore_TESTING_ENABLED "Enable libcore testing" OFF)

if(libcore_TESTING_ENABLED)
  message(STATUS "libcore testing enabled")
  enable_testing()
endif()

find_package(fmt REQUIRED)
find_package(Threads REQUIRED)

# Add third-party libraries
if (NOT TARGET gtest)
  add_subdirectory(third_party/gtest)
endif()
add_subdirectory(public_types)
add_subdirectory(utilities)

# Doxygen setup
if (libcore_DOXYGEN_BUILD_ENABLED)
  message(STATUS "libcore doxygen build enabled")
  add_subdirectory(doxygen)
else()
  message(STATUS "libcore doxygen build disabled")
endif()
