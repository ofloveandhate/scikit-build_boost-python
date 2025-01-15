#include "example_pycpp.hpp"

std::string foo(){
	std::stringstream ss;
	ss << example::core_function();
	return ss.str();
}


using namespace boost::python;


void export_functions(){
	def("foo",foo, "print a nice message");

}