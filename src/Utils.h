#pragma once
#include <vector>
#include <string>
#include <algorithm>


std::vector<std::string> split_string(const std::string &str, const char &s, bool remove_empties = true);

template <typename I, typename FilterType, typename FuncType>
void for_each_if(I begin, I end, FilterType if_func, FuncType apply_func)
{
    auto fil_app = [if_func, apply_func](auto &item){if(if_func(item)) apply_func(item);};
    std::for_each(begin, end, fil_app);
}
