#include "Utils.h"

std::vector<std::string> split_string(const std::string &str, const char &s, bool remove_empties /*= true*/)
{
    std::vector<std::string> result;

    std::string::size_type begin = 0;
    std::string::size_type end = str.find_first_of(s);
    while (end != std::string::npos)
    {
        result.push_back(str.substr(begin, end - begin));
        begin = end + 1;
        end = str.find_first_of(s, begin);
    }

    result.push_back(str.substr(begin, end));
    if (remove_empties)
    {
        result.erase(std::remove_if(result.begin(), result.end(), [] (const auto &item) {return item.empty();}), result.end());
    }
    return result;
}

