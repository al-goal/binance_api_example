#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include "output_callback.hpp"
#include "micro_sax_parser.hpp"

int main(int argc, char* argv[])
{
    std::string path = "/home/aln/binance_api_example/sample.txt";
    std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
    ifs.ignore( std::numeric_limits<std::streamsize>::max() );
    std::streamsize length = ifs.gcount();
    ifs.clear();   //  Since ignore will have set eof.
    ifs.seekg( 0, std::ios_base::beg );

    binance_api_example::OutputCallback callback(std::cout);
    binance_api_example::parse_stream(ifs, length, callback);
    return 0;
}