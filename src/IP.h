#pragma once
#include <vector>
#include <string>

namespace ip
{

    enum version
    {
        IPv4 = 4,
        IPv6 = 6
    };

    enum format
    {
        decimal,
        hex
    };

    class Address
    {
        
    private:
        friend bool cmp_ips_desc(const Address &a, const Address &b);
        version ver;
        std::vector<unsigned char> address;
    public:
        std::string str() const;
        void fill_addr(const std::vector<std::string> &addr);
        void fill_addr(const std::vector<int> &addr);
        const std::vector<unsigned char>& getaddress() const;
        Address(const version &c);
        ~Address();
    };

    bool cmp_ips_asc(const Address &a, const Address &b);
    bool cmp_ips_desc(const Address &a, const Address &b);

}