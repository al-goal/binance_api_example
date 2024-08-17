#ifndef OUTPUT_CALLBACK_HPP
#define OUTPUT_CALLBACK_HPP

#include "parser_interface.hpp"
#include <vector>
#include <ostream>

namespace binance_api_example
{

class OutputCallback : public binance_api_example::CallbackInterface
{

public:

    OutputCallback(std::ostream& os)
    :   os(os)
    {
    }    

    void start_array() override
    {
        enable_output = true;
    }

    void end_array() override
    {
        enable_output = false;
    }

    void start_object() override
    {
        keys.clear();
        values.clear();
    }

    void end_object() override
    {
        if (enable_output)
        {
            os << "[" << std::endl;
            os << "  {" << std::endl;
            for (int i = 0; i < keys.size(); i++)
            {
                os << "    " << keys[i] << ": " << values[i] << "," << std::endl;
            }
            os << "  }" << std::endl;
            os << "]" << std::endl;
        }
        keys.clear();
        values.clear();
    }

    void key(const std::string& key) override
    {
        keys.push_back(key);
    }

    void value(const std::string& value) override
    {
        values.push_back(value);
    }

private:

    std::ostream& os;
    bool enable_output = false;
    std::vector<std::string> keys;
    std::vector<std::string> values;
};

} // namespace binance_api_example

#endif // OUTPUT_CALLBACK_HPP