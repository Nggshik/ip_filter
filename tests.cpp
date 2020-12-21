#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>
#include <vector>
#include "ip_filter.hpp"
#include "lib.h"

BOOST_AUTO_TEST_SUITE(ip_filter_test_version)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_isMatch)
{
    //TEST1
    std::vector<std::string> ip1{"255","127","1","1"};
    
    BOOST_CHECK(isMatch(ip1.cbegin(),ip1.cend(),255,127) == true);
    BOOST_CHECK(isMatch(ip1.cbegin(),ip1.cend(),255) == true);
    BOOST_CHECK(isMatch(ip1.cbegin(),ip1.cend(),255,127,1,1) == true);
    BOOST_CHECK(isMatch(ip1.cbegin(),ip1.cend(),255,127,2,0) == false);
}

BOOST_AUTO_TEST_CASE(ip_filter_comparator)
{
    //TEST1
    std::vector<std::vector<std::string>> ip1{{"255","127","1","1"},{"255","127","1","1"},{"254","127","1","1"}};
    
    BOOST_CHECK(compareIpVector(ip1[0],ip1[1]) == false);
    BOOST_CHECK(compareIpVector(ip1[0],ip1[2]) == true);
    BOOST_CHECK(compareIpVector(ip1[2],ip1[1]) == false);
    BOOST_CHECK(compareIpVector(ip1[1],ip1[2]) == true);
}

BOOST_AUTO_TEST_SUITE_END()