#include "example/core.hpp"

namespace example{


using boost::multiprecision::pow;

mpfr_float core_function(){
	return pow(mpfr_float(2),mpfr_float(1) / mpfr_float(12));
}

}