add_library(public-types INTERFACE)

target_include_directories(public-types
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (libcore_TESTING_ENABLED)
  add_executable(unit-test-public-types
    test/test_error_codes.cc
    test/test_span.cc
  )
  target_link_libraries(unit-test-public-types
    gtest
    gtest_main
    public-types
  )
  add_test(NAME unit-test-public-types COMMAND unit-test-public-types)
endif()
