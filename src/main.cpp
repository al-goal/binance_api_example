#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include "output_callback.hpp"
#include "micro_sax_parser.hpp"

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

size_t write_function(void *ptr, size_t size, size_t nmemb, void* data) {
    binance_api_example::Parser *parser = (binance_api_example::Parser*) data;

    for (int i = 0; i < size * nmemb; i++)
    {
        parser->parse_char(((char*) ptr)[i]);
    }

    return size * nmemb;
}

int main(int argc, char* argv[])
{
    // std::string path = "/home/aln/binance_api_example/sample.txt";
    // std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
    // ifs.ignore( std::numeric_limits<std::streamsize>::max() );
    // std::streamsize length = ifs.gcount();
    // ifs.clear();   //  Since ignore will have set eof.
    // ifs.seekg( 0, std::ios_base::beg );

    binance_api_example::OutputCallback output_callback = binance_api_example::OutputCallback(std::cout);
    output_callback.start_object();
    binance_api_example::Parser parser(output_callback);

    auto curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=GUSDT");
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parser);

        char* url;
        long response_code;
        double elapsed;
        

        curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        curl_easy_cleanup(curl);
        curl = NULL;

        // std::cout << "Response code: " << response_code << std::endl;
        // std::cout << "Elapsed time: " << elapsed << std::endl;
        // std::cout << "Effective URL: " << url << std::endl; 
        // // std::cout << "Response string: " << response_string << std::endl;
        // std::cout << "Header string: " << header_string << std::endl;

        std::istringstream iss(response_string);

        binance_api_example::OutputCallback callback(std::cout);
        binance_api_example::parse_stream(iss, response_string.size(), callback);
    }

    // binance_api_example::OutputCallback callback(std::cout);
    // binance_api_example::parse_stream(ifs, length, callback);
    // return 0;
}