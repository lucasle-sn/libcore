add_library(utilities
  src/bytestream.cc
  src/clog.cc
  src/log_config.cc
  src/log.cc
  src/thread.cc
)
target_include_directories(utilities
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(utilities
  PUBLIC public-types Threads::Threads fmt::fmt
)

add_library(test-utilities
  src/test_fixture.cc
)
target_include_directories(test-utilities
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(test-utilities
  PUBLIC gtest gtest_main utilities
)

if(libcore_TESTING_ENABLED)
  add_executable(unit-test-utilities
    test/test_bytestream.cc
    test/test_thread.cc
  )
  target_link_libraries(unit-test-utilities
    gtest
    gtest_main
    utilities
    test-utilities
  )
  add_test(NAME unit-test-utilities COMMAND unit-test-utilities)

  add_executable(unit-test-utilities-logger
    test/test_clog.cc
    test/test_log_config.cc
    test/test_log.cc
  )
  target_link_libraries(unit-test-utilities-logger
    gtest
    gtest_main
    utilities
    test-utilities
  )
  add_test(NAME unit-test-utilities-logger COMMAND unit-test-utilities-logger)
endif()
