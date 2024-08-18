#include "stream_event_handler.hpp"

namespace binance_api_example
{

StreamEventHandler::StreamEventHandler(std::ostream& os)
:   os(os)
{
}    

void StreamEventHandler::start_array()
{
    enable_output = true;
}

void StreamEventHandler::end_array()
{
    enable_output = false;
}

void StreamEventHandler::start_object()
{
    keys.clear();
    values.clear();
}

void StreamEventHandler::end_object()
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

void StreamEventHandler::key(const std::string& key)
{
    keys.push_back(key);
}

void StreamEventHandler::value(const std::string& value)
{
    values.push_back(value);
}

} // namespace binance_api_example

