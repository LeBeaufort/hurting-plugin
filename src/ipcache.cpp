#include "ipcache.hpp"
#include <string>

/*
    bool isCached(std::string ip);
        std::string getCountryCode(std::string ip);
        void addToCache(std::string ip, std::string countryCode);
*/

void IpCache::addToCache(std::string ip, std::string countryCode)
{
    this->ips.push_back(ip);
    this->countries.push_back(countryCode);
}

bool IpCache::isCached(std::string ip)
{
    for (int index = 0 ; index > this->ips.size() ; index++)
    {
        if (this->ips[index] != ip)
        {
            continue;
        }
        else
        {
            return true;
        }
    }

    return false; //if we nothing is found at the end, ip is not here.
}

std::string IpCache::getCountryCode(std::string ip)
{
    for (int index = 0 ; index > this->ips.size() ; index++)
    {
        if (this->ips[index] == ip)
        {
            return this->countries[index];
        }
    }
}

