#define BOOST_TEST_MODULE ip_filter_tests

#include <boost/test/unit_test.hpp>
#include "lib.h"

BOOST_AUTO_TEST_SUITE(ip_filter_tests)

BOOST_AUTO_TEST_CASE(ip_filter_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()