#ifndef IPCACHE_HPP
#define IPCACHE_HPP

#include <string>
#include <vector>

class IpCache
{
    private:
        std::vector<std::string> ip;
        std::vector<std::string> countries;
    
    public:
        
        bool isCached(std::string ip);
        std::string getCountryCode(std::string ip);
        void addToCache(std::string ip, std::string countryCode);

}


#endif IPCACHE_HPP