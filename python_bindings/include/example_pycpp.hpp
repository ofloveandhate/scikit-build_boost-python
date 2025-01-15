#pragma once

#ifndef PRECOMPILED_PYTHON_BINDINGS_USING_BOOST_HPP
#define PRECOMPILED_PYTHON_BINDINGS_USING_BOOST_HPP



#include <boost/python.hpp>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/args.hpp>
#include <boost/python/class.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/register_ptr_to_python.hpp>


#include <string>

#include <example/core.hpp>

using namespace boost::python;

using mpfr_float = example::mpfr_float;

// the function we're going to export
std::string foo();




void export_functions();

BOOST_PYTHON_MODULE(_example) // this name must match the name of the generated .so file.
{
	// see https://stackoverflow.com/questions/6114462/how-to-override-the-automatically-created-docstring-data-for-boostpython
	// docstring_options d(true, true, false); // local_
	docstring_options docopt;
	docopt.enable_all();
	docopt.disable_cpp_signatures();

	object package = scope();
    package.attr("__path__") = "__example";

    export_functions();
}

#endif