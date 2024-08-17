cmake_minimum_required(VERSION 3.10)
project (binance_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# enable_testing()

add_executable(
  binance_api
  micro_sax_parser.cpp
  main.cpp
)

target_link_libraries(
  binance_api
  curl
)

# target_include_directories(
#     test_hash_map PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>
# )

# include(GoogleTest)
# gtest_discover_tests(test_hash_map)