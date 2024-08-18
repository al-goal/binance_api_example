#ifndef BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP
#define BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP

#include "parser_interface.hpp"

namespace binance_api_example
{

class MiniJsonParser
{
public:

    MiniJsonParser(CallbackInterface& callback);

    void parse_char(char c);

private:

    CallbackInterface& callback;
    std::string buffer;
};

} // namespace binance_api_example

#endif // BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP