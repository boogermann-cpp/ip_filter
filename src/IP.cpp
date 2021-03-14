#include "IP.h"
#include <stdexcept>

using namespace ip;

Address::Address(const version &c):ver(c)
{
}

std::string Address::str() const
{
    std::string str("");
    for(auto it = address.begin(); it != address.end();)
    {
        str.append(std::to_string(*it));
        ++it;
        if (it != address.end()) str.append(".");
    }
    return str;
}

void Address::fill_addr(const std::vector<std::string> &addr)
{
    address.clear();
    for (auto it = addr.begin(); it != addr.end(); ++it)
    {
        auto octet = std::stoul(*it);
        if (octet <= 0xff) address.push_back(static_cast<unsigned char>(octet));
        else throw std::out_of_range("IP octet out-of-range");
    }
}

const std::vector<unsigned char>& Address::getaddress() const
{
    return address;
}

void Address::fill_addr(const std::vector<int> &addr)
{
    address.clear();
    for (auto it = addr.begin(); it != addr.end(); ++it)
    {
        if (*it <= 0xff) address.push_back(static_cast<unsigned char>(*it));
        else throw std::out_of_range("IP octet out-of-range");
    }
}

Address::~Address()
{
}

bool ip::cmp_ips_desc(const Address &a, const Address &b)
{
    if (a.ver != b.ver) throw std::logic_error("Comparison between different IP types is prohibited");
    else
    {
        auto ita = a.address.begin();
        auto itb = b.address.begin();
        for (; ita != a.address.end(); ++ita, ++itb)
        {
            if (*ita > *itb) return true;
            else if (*ita < *itb) return false;
        }
    }
    return false;
}

bool ip::cmp_ips_asc(const Address &a, const Address &b)
{
    return !ip::cmp_ips_desc(a, b);
}