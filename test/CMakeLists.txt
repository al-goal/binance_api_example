enable_testing()

add_executable(
  test_binance_api_example
  test_output_callback.cpp
  test_parser.cpp
)

target_link_libraries(
  test_binance_api_example
  binance_api_parse
  GTest::gtest_main
)

target_include_directories(
  test_binance_api_example PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>
)

include(GoogleTest)
gtest_discover_tests(test_binance_api_example)