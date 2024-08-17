#ifndef PARSER_INTERFACE_HPP
#define PARSER_INTERFACE_HPP

#include <string>

namespace binance_api_example
{

class CallbackInterface
{
public:

    virtual void start_array() {};
    virtual void end_array() {};
    virtual void start_object() {};
    virtual void end_object() {};
    virtual void key(const std::string& key) {};
    virtual void value(const std::string& value) {};
};

}

#endif // PARSER_INTERFACE_HPP