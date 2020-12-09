#include "ip_filter.hpp"
#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>
#include <vector>
#include "lib.h"

bool compareIpVector(const ipAddress& firstIp, const ipAddress& secondIp)
{
    // assert(firstIp.size() == 4);
    
    for(int ip_part = 0;ip_part < 4;++ip_part)
    {
        if(firstIp[ip_part] > secondIp[ip_part])
        {
            return true;
        }
        else if(firstIp[ip_part] < secondIp[ip_part])
        {
            return false;
        }
    }
    return false;
}

BOOST_AUTO_TEST_SUITE(ip_filter_tests)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_comparator)
{
    //TEST1
    std::vector<std::string> ip1{"255","127","1","1"};
    std::vector<std::string> ip2{"127","127","1","1"};
    
    BOOST_CHECK(compareIpVector(ip1,ip2) == true);
    BOOST_CHECK(compareIpVector(ip2,ip1) == false);
    BOOST_CHECK(compareIpVector(ip1,ip1) == false);
    BOOST_CHECK(compareIpVector(ip2,ip2) == false);
}

BOOST_AUTO_TEST_SUITE_END()