

//TODO: make the DYN_LINK change depending on the targeted architecture.  some need it, others don't.
//if used, BOOST_TEST_DYN_LINK must appear before #include <boost/test/unit_test.hpp>
#define BOOST_TEST_DYN_LINK


//this #define MUST appear before #include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE "Example Core Library Testing"
#include <boost/test/unit_test.hpp>


#define BERTINI_TEST_MODULE "Module 1"

#include "example/core.hpp"







BOOST_AUTO_TEST_SUITE(Suite_A)



BOOST_AUTO_TEST_CASE(test_i)
{
	BOOST_CHECK_CLOSE(example::core_function(), 1.05946309, 1e-6);
}


BOOST_AUTO_TEST_SUITE_END()
