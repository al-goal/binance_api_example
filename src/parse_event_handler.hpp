#ifndef BINANCE_API_EXAMPLE_PARSE_EVENT_HANDLER_HPP
#define BINANCE_API_EXAMPLE_PARSE_EVENT_HANDLER_HPP

#include <string>

namespace binance_api_example
{

class ParseEventHandler
{
public:

    virtual void start_array() {};
    virtual void end_array() {};
    virtual void start_object() {};
    virtual void end_object() {};
    virtual void key(const std::string& key) {};
    virtual void value(const std::string& value) {};
};

} //namespace binance_api_example

#endif // BINANCE_API_EXAMPLE_PARSE_EVENT_HANDLER_HPP