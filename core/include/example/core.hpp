#pragma once
#ifndef CORE_HPP
#define CORE_HPP


#include <string>
#include <boost/multiprecision/mpfr.hpp>


namespace example{

using mpfr_float = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_on>;

mpfr_float core_function();

};

#endif
