#include "example/executable.hpp"


namespace example{

std::string executable_function(){
	std::stringstream ss;
	ss << core_function() << " " << "hello from the executable";
	return ss.str();
}

}


int main(int argc, char const *argv[])
{
	std::cout << example::executable_function() << std::endl;
	return 0;
}
