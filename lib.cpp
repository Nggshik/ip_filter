#include "lib.h"
#include "version.h"

int version()
{
    return PROJECT_VERSION_PATCH;
} 

bool compareIpVector(const std::vector<std::string>& firstIp, const std::vector<std::string>& secondIp)
{
    assert(firstIp.size() == 4);
    
    for(int ip_part = 0;ip_part < 4;++ip_part)
    {
        if(std::stoi(firstIp[ip_part]) > std::stoi(secondIp[ip_part]))
        {
            return true;
        }
        else if(std::stoi(firstIp[ip_part]) < std::stoi(secondIp[ip_part]))
        {
            return false;
        }
    }
    return false;
}