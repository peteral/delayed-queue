#define BOOST_TEST_MODULE First_TestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MyTest)
{
    BOOST_CHECK_EQUAL(1, 2);
}
