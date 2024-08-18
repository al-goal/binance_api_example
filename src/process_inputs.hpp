#ifndef BINANCE_API_EXAMPLE_PROCESS_INPUTS_HPP
#define BINANCE_API_EXAMPLE_PROCESS_INPUTS_HPP

#include <string>
#include <iostream>

namespace binance_api_example
{

void process_url_to_stream(std::string url, std::ostream& os = std::cout, bool use_buffer = false);
void process_stream(std::istream& is, std::ostream& os = std::cout);

}

#endif // BINANCE_API_EXAMPLE_PROCESS_INPUTS_HPP