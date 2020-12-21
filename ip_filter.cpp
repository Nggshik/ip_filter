#include "ip_filter.hpp"
#include "lib.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
ipAddress split(const std::string &str, char d)
{
    ipAddress r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void printIpPool(const ipList& list)
{
        for(auto ip = list.cbegin(); ip != list.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            
            std::cout << std::endl;
        }
}



int main(int argc, char const *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    try
    {
        ipList ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            ipAddress v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](const ipAddress& ip1, const ipAddress& ip2){return compareIpVector(ip1,ip2);});
        
        printIpPool(ip_pool);

        // auto rs = isMatch(ip_pool[0].cbegin(),ip_pool[0].cend(),222);
        auto filter = [&ip_pool](auto... args)
                        {
                            ipList flList;
                            for(auto const& ip : ip_pool) 
                            {
                                if(isMatch(ip.cbegin(),ip.cend(),args...))
                                 flList.push_back(ip);
                            }
                            return flList;
                        };
       auto filter_any = [&ip_pool](int val)
                        {
                            ipList flList;
                            std::copy_if(ip_pool.cbegin(),ip_pool.cend(),std::back_inserter(flList),
                                [val](auto ip){
                                    return std::any_of(ip.cbegin(),ip.cend(),[val](auto decade){return std::stoi(decade) == val;});
                                    });
                            
                            return flList;
                        };
        auto ip = filter(1);
        printIpPool(ip);

        ip = filter(46,70);
        printIpPool(ip);

        ip = filter_any(46);
        printIpPool(ip);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
