#ifndef BINANCE_API_EXAMPLE_STREAM_EVENT_HANDLER_HPP
#define BINANCE_API_EXAMPLE_STREAM_EVENT_HANDLER_HPP

#include "parse_event_handler.hpp"
#include <vector>
#include <ostream>

namespace binance_api_example
{

class StreamEventHandler : public binance_api_example::ParseEventHandler
{

public:

    StreamEventHandler(std::ostream& os);

    void start_array() override; 
    void end_array() override;
    void start_object() override;
    void end_object() override;
    void key(const std::string& key) override;
    void value(const std::string& value) override;

private:

    std::ostream& os;
    bool enable_output = false;
    std::vector<std::string> keys;
    std::vector<std::string> values;
};

} // namespace binance_api_example

#endif // BINANCE_API_EXAMPLE_STREAM_EVENT_HANDLER_HPP