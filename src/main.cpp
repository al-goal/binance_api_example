#include "process_inputs.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <symbol>" << std::endl;
        std::cerr << "A test symbol is GUSDT" << std::endl;
        return 1;
    }

    std::string symbol(argv[1]);
    std::string url("https://fapi.binance.com/fapi/v1/aggTrades?symbol=" + symbol);
    try
    {
        binance_api_example::process_url_to_stream(url, std::cout, false);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
 }