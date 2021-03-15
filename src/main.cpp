#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>

#include "IP.h"
#include "Utils.h"

using StringVec = typename std::vector<std::string>;
namespace fs = std::experimental::filesystem;

int main(int argc, char** argv)
{

    std::vector<ip::Address> address_list;
    std::istream* input_stream;


    if (argc == 1)
    {
        input_stream = &std::cin;
    }
    else if (argc == 2)
    {
        std::ifstream* in_file = new std::ifstream();
        input_stream = in_file;
        
        fs::path path = fs::path(fs::current_path());
        path /= argv[1];
        in_file->open(path);
        
        if (!in_file->is_open())
        {
            std::cout << "Error: Input file not found." << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Please run the application without parameters and pass input stream as a standard input/n\
                        or set input file as the only argument of the command line/n\
                        Example: ip_filter [path]" << std::endl;
        return 1;
    }
        

    for(std::string str; std::getline(*input_stream, str);)
    {
        StringVec cols = split_string(str, '\t');
        StringVec ips = split_string(cols.at(0), '.');
        auto address = ip::Address(ip::IPv4);
        address.fill_addr(ips);
        address_list.push_back(address);
    }

    std::sort(address_list.begin(), address_list.end(), ip::cmp_ips_desc);

    auto print = [](const ip::Address &addr){std::cout << addr.str() << std::endl;};

    for(auto it = address_list.begin(); it != address_list.end(); ++it)
    {
        print(*it);
    }

    std::vector<std::function<bool(const ip::Address &)>> filters;
    filters.push_back([](const ip::Address &addr){return (addr.getaddress()[0] == 1);});
    filters.push_back([](const ip::Address &addr){return (addr.getaddress()[0] == 46 && addr.getaddress()[1] == 70);});
    filters.push_back([](const ip::Address &addr){return (std::any_of(addr.getaddress().begin(), addr.getaddress().end(), 
                                                                                [](auto &octet){return octet == 46;}));});

    for(auto filter = filters.begin(); filter != filters.end(); ++filter)
    {
        for_each_if(address_list.begin(), address_list.end(), *filter, print);
    }

    return 0;
}

//TODO:
// + Add using typename
// + make Util lib
// + make shell-based test
// + make unit tests for sorting, string_split
// - apply clang-format