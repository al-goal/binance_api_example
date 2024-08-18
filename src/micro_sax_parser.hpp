#ifndef BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP
#define BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP

#include <istream>
#include "parser_interface.hpp"

namespace binance_api_example
{

/// @brief Parses an input stream
/// @param ifs 
/// @param length 
/// @param callback 
void parse_stream (std::istream& ifs, int length, CallbackInterface& callback);

class Parser
{
public:

    Parser(CallbackInterface& callback);

    void parse_char(char c);

private:

    CallbackInterface& callback;
    std::string buffer;
};

} // namespace binance_api_example

#endif // BINANCE_API_EXAMPLE_MICRO_SAX_PARSER_HPP