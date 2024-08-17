#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include "parser_interface.hpp"
#include "micro_sax_parser.hpp"

// void start_array()
// {
//     std::cout << "Start array" << std::endl;
// }

// void start_object()
// {
//     std::cout << "Start object" << std::endl;
// }

// void end_object()
// {
//     std::cout << "End object" << std::endl;
// }

// void key(std::string key)
// {
//     std::cout << "Key: " << key << std::endl;
// }


// void value(std::string value)
// {
//     std::cout << "Value: " << value << std::endl;
// }

class MyCallback : public binance_api_example::CallbackInterface
{

public:

    void start_array() override
    {
        std::cout << "start array" << std::endl;
    }

    void end_array() override
    {
        std::cout << "end array" << std::endl;
    }

    void start_object() override
    {
        std::cout << "start object" << std::endl;
        keys.clear();
        values.clear();
    }

    void end_object() override
    {
        // std::cout << "end object " << keys.size() << " " << values.size() << std::endl;
        std::cout << "[" << std::endl;
        std::cout << "  {" << std::endl;
        for (int i = 0; i < keys.size(); i++)
        {
            std::cout << "    " << keys[i] << ": " << values[i] << std::endl;
        }
        std::cout << "  }" << std::endl;
        std::cout << "]" << std::endl;
    }

    void key(const std::string& key) override
    {
        keys.push_back(key);
    }

    void value(const std::string& value) override
    {
        std::cout << "value: " << value << std::endl;
        values.push_back(value);
    }

private:

    std::vector<std::string> keys;
    std::vector<std::string> values;
};

int main(int argc, char* argv[])
{
    std::string path = "/home/aln/binance_api_example/sample.txt";
    std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
    ifs.ignore( std::numeric_limits<std::streamsize>::max() );
    std::streamsize length = ifs.gcount();
    ifs.clear();   //  Since ignore will have set eof.
    ifs.seekg( 0, std::ios_base::beg );

    MyCallback callback;
    binance_api_example::parse_stream(ifs, length, callback);

    // std::string buffer;
    // for (int i = 0; i < length; i++)
    // {
    //     char c;
    //     ifs.get(c);
    //     buffer.append(1, c);
        // if (buffer == "[")
        // {
        //     start_array();
        //     buffer.clear(); 
        // }
        // else if (buffer == "{")
        // {
        //     start_object();
        //     buffer.clear();
        // }
        // else if (c == '}')
        // {
        //     buffer.erase(buffer.size() - 1);
        //     value(buffer);
        //     end_object();
        //     buffer.clear();
        // }
        // else if (c == ']')
        // {
        //     buffer.clear();
        // }
        // else if (c == ':')
        // {
        //     buffer.erase(buffer.size() - 1);
        //     key(buffer);
        //     buffer.clear();
        // }
        // else if (c == ',')
        // {
        //     buffer.erase(buffer.size() - 1);
        //     value(buffer);
        //     buffer.clear();
        // }
        // else
    //     {
    //         /* code */
    //     }
         
    // }

    std::cout << length << std::endl;
}