#include "micro_sax_parser.hpp"
#include <iostream>

namespace binance_api_example
{

void parse_stream (std::istream& ifs, int length, CallbackInterface& callback)
{
    std::string buffer;
    for (int i = 0; i < length; i++)
    {
        char c;
        ifs.get(c);
        buffer.append(1, c);

        std::cout << "c: " << c << " " << buffer << std::endl; 
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
            buffer.erase(buffer.size() - 1);
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
            buffer.erase(buffer.size() - 1);
            callback.key(buffer);
            buffer.clear();
        }
        else if (c == ',')
        {
            if (buffer.size() > 1)
            {
                buffer.erase(buffer.size() - 1);
                callback.value(buffer);
            }
            buffer.clear();
        }
    }
}

Parser::Parser(CallbackInterface& callback)
:   callback(callback)
{
}

void Parser::parse_char(char c)
{
    buffer.append(1, c);

    // std::cout << "buffer: " <<  buffer << std::endl;

    // std::cout << "c: " << c << " " << buffer << std::endl; 
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
        buffer.erase(buffer.size() - 1);
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
        buffer.erase(buffer.size() - 1);
        callback.key(buffer);
        buffer.clear();
    }
    else if (c == ',')
    {
        if (buffer.size() > 1)
        {
            buffer.erase(buffer.size() - 1);
            callback.value(buffer);
        }
        buffer.clear();
    }
}

} // namespace binance_api_example