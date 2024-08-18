#include "mini_json_parser.hpp"
#include <iostream>

namespace binance_api_example
{

MiniJsonParser::MiniJsonParser(ParseEventHandler& event_handler)
:   event_handler(event_handler)
{
}

void MiniJsonParser::parse_char(char c)
{
    if (c == '[')
    {
        event_handler.start_array();
        buffer.clear(); 
    }
    else if (c == '{')
    {
        event_handler.start_object();
        buffer.clear();
    }
    else if (c == '}')
    {
        event_handler.value(buffer);
        event_handler.end_object();
        buffer.clear();
    }
    else if (c == ']')
    {
        buffer.clear();
    }
    else if (c == ':')
    {
        event_handler.key(buffer);
        buffer.clear();
    }
    else if (c == ',')
    {
        event_handler.value(buffer);
        buffer.clear();
    }
    else
    {
        buffer.append(1, c);
    }
}

} // namespace binance_api_example