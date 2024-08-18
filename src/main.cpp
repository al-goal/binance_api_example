#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include "stream_event_handler.hpp"
#include "mini_json_parser.hpp"

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

size_t write_function(void *ptr, size_t size, size_t nmemb, void* data) {
    binance_api_example::MiniJsonParser *parser = (binance_api_example::MiniJsonParser*) data;

    for (int i = 0; i < size * nmemb; i++)
    {
        parser->parse_char(((char*) ptr)[i]);
    }

    return size * nmemb;
}

int main(int argc, char* argv[])
{
    binance_api_example::StreamEventHandler output_callback = binance_api_example::StreamEventHandler(std::cout);
    binance_api_example::MiniJsonParser parser(output_callback);

    auto curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=GUSDT");
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
    }

    // binance_api_example::StreamEventHandler callback(std::cout);
    // binance_api_example::parse_stream(ifs, length, callback);
    // return 0;
}