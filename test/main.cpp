#include "gtest/gtest.h"
#include "IP.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Utils.h"

TEST(version, ip_filled_with_ints_test)
{
    ip::Address A = ip::Address(ip::IPv4);
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    A.fill_addr(vec);

    EXPECT_EQ(A.str(), std::string("1.2.3.4"));
}

TEST(version, ip_filled_with_strings_test)
{
    ip::Address A = ip::Address(ip::IPv4);
    std::vector<std::string> vec;
    vec.push_back(std::string("0"));
    vec.push_back(std::string("1"));
    vec.push_back(std::string("2"));
    vec.push_back(std::string("255"));
    A.fill_addr(vec);

    EXPECT_EQ(A.str(), std::string("0.1.2.255"));
}

TEST(version, ip_filled_with_out_of_range_strings_test)
{
    try
    {
        ip::Address A = ip::Address(ip::IPv4);
        std::vector<std::string> vec;
        vec.push_back(std::string("0"));
        vec.push_back(std::string("1"));
        vec.push_back(std::string("2"));
        vec.push_back(std::string("256"));
        A.fill_addr(vec);
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("IP octet out-of-range"));
    }
    catch(...)
    {
        FAIL();
    }

}

TEST(version, ip_filled_with_out_of_range_ints_test)
{
    try
    {
        ip::Address A = ip::Address(ip::IPv4);
        std::vector<int> vec;
        vec.push_back(1000);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        A.fill_addr(vec);
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("IP octet out-of-range"));
    }
    catch(...)
    {
        FAIL();
    }

}

TEST(version, split_string_no_empties_test)
{
    std::vector<std::string> expected;
    expected.push_back(std::string("This"));
    expected.push_back(std::string("is"));
    expected.push_back(std::string("a"));
    expected.push_back(std::string("String\n"));
    const char delimiter = ' ';
    std::string input;
    for (auto it = expected.begin(); it != expected.end();)
    {
        input += *it;
        ++it;
        if (it != expected.end())
        {
            input.push_back(delimiter);
        }
    }
    auto output = split_string(input, delimiter);
    EXPECT_EQ(output, expected);

}

TEST(version, split_string_empties_test)
{
    std::vector<std::string> expected;
    expected.push_back(std::string("192"));
    expected.push_back(std::string("168"));
    expected.push_back(std::string("0"));
    expected.push_back(std::string(""));
    const char delimiter = 'p';
    std::string input;
    for (auto it = expected.begin(); it != expected.end(); ++it)
    {
        input += *it;
        input.push_back(delimiter);
    }
    auto output = split_string(input, delimiter, false);
    expected.push_back(std::string());
    EXPECT_EQ(output, expected);

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
