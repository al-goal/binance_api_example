#include "mini_json_parser.hpp"
#include <iostream>

namespace binance_api_example
{

MiniJsonParser::MiniJsonParser(ParseEventHandler& callback)
:   callback(callback)
{
}

void MiniJsonParser::parse_char(char c)
{
    if (c == '[')
    {
        callback.start_array();
        buffer.clear(); 
    }
    else if (c == '{')
    {
        callback.start_object();
        buffer.clear();
    }
    else if (c == '}')
    {
        callback.value(buffer);
        callback.end_object();
        buffer.clear();
    }
    else if (c == ']')
    {
        buffer.clear();
    }
    else if (c == ':')
    {
        callback.key(buffer);
        buffer.clear();
    }
    else if (c == ',')
    {
        callback.value(buffer);
        buffer.clear();
    }
    else
    {
        buffer.append(1, c);
    }
}

} // namespace binance_api_example