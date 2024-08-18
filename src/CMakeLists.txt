add_library(
    binance_api_parse
    mini_json_parser.cpp
    stream_event_handler.cpp
)

add_executable(
    binance_api_example
    main.cpp
)

target_link_libraries(
    binance_api_example
    binance_api_parse
    curl
)
