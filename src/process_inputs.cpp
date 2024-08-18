#include <curl/curl.h>
#include <sstream>
#include "process_inputs.hpp"
#include "stream_event_handler.hpp"
#include "mini_json_parser.hpp"

namespace binance_api_example
{

static size_t write_function_buffered(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

static size_t write_function_direct(void *ptr, size_t size, size_t nmemb, void* data) {
    MiniJsonParser *parser = (binance_api_example::MiniJsonParser*) data;

    for (int i = 0; i < size * nmemb; i++)
    {
        parser->parse_char(((char*) ptr)[i]);
    }

    return size * nmemb;
}

void process_url_to_stream(std::string url, std::ostream& os, bool use_buffer)
{
    auto curl = curl_easy_init();
    if (curl)
    {
        StreamEventHandler event_handler(os);
        MiniJsonParser parser(event_handler);
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        if (use_buffer)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_buffered);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_direct);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &parser);

        }
        curl_easy_perform(curl);

        if (use_buffer)
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code != 200)
            {
                os << "Error: " << response_code << std::endl;
                return;
            }
            std::istringstream is(response_string);
            process_stream(is, os);
        }

        curl_easy_cleanup(curl);
        curl = NULL;
    }
}

void process_stream(std::istream& is, std::ostream& os)
{
    StreamEventHandler handler(os);
    MiniJsonParser parser(handler);

    while (is)
    {
        char c;
        is.get(c);
        parser.parse_char(c);
    }
}

} // namespace binance_api_example