#include "issorted_andhow.h"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_ascending)
{
  BOOST_REQUIRE_EQUAL(WARS::isSortedAndHow({1,2,3,4}), "yes, ascending");
}

BOOST_AUTO_TEST_CASE(test_decending)
{
  BOOST_REQUIRE_EQUAL(WARS::isSortedAndHow({5,4,3,2,1}), "yes, descending");
}

BOOST_AUTO_TEST_CASE(test_negative)
{
  BOOST_REQUIRE_EQUAL(WARS::isSortedAndHow({-1,-2,-3,-4}), "yes, descending");
}

BOOST_AUTO_TEST_CASE(test_not_sorted)
{
  BOOST_REQUIRE_EQUAL(WARS::isSortedAndHow({1,2,10,3,4}), "no");
}

BOOST_AUTO_TEST_CASE(test_null)
{
  BOOST_REQUIRE_EQUAL(WARS::isSortedAndHow({}), "");
}


// To run tests: g++ -std=c++0x isdortes_andhow_tests.cpp && ./a.out && rm a.out

