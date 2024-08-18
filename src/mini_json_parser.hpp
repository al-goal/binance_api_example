#ifndef BINANCE_API_EXAMPLE_MINI_JSON_PARSER_HPP
#define BINANCE_API_EXAMPLE_MINI_JSON_PARSER_HPP

#include "parse_event_handler.hpp"

namespace binance_api_example
{

class MiniJsonParser
{
public:

    MiniJsonParser(ParseEventHandler& event_handler);

    void parse_char(char c);

private:

    ParseEventHandler& event_handler;
    std::string buffer;
};

} // namespace binance_api_example

#endif // BINANCE_API_EXAMPLE_MINI_JSON_PARSER_HPP