cmake_minimum_required(VERSION 3.22)



find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

find_package(Boost COMPONENTS system python3 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})



# list the sources

set(SOURCES
	src/example_pycpp.cpp
)

set(HEADERS
	include/example_pycpp.hpp
)


target_include_directories(example_compiled_python_bindings PUBLIC "include/")

target_sources(example_compiled_python_bindings PUBLIC ${SOURCES} ${HEADERS})

target_link_libraries(example_compiled_python_bindings PRIVATE ${Boost_LIBRARIES} example_core_lib)


# trying to get it to install to the correct directory
# https://stackoverflow.com/questions/1242904/finding-python-site-packages-directory-with-cmake

# https://github.com/scikit-build/scikit-build-sample-projects/blob/main/projects/hello-cmake-package/CMakeLists.txt






# We are using the SKBUILD variable, which is defined when scikit-build is
# running the CMake build, to control building the Python wrapper. This allows
# the C++ project to be installed, standalone, when using the standard CMake
# build flow.
if(DEFINED SKBUILD)

		

	install(TARGETS example_compiled_python_bindings LIBRARY DESTINATION .)


	# The extension module must load the hello library as a dependency when the
	# extension module is loaded. The easiest way to locate the hello library is
	# via RPATH. Absolute RPATHs are possible, but they make the resulting
	# binaries not redistributable to other Python installations (conda is broke,
	# wheel reuse is broke, and more!).
	#
	# Placing the hello library in the package and using relative RPATHs that
	# doesn't point outside of the package means that the built package is
	# relocatable. This allows for safe binary redistribution.
	if(APPLE)
	  set_target_properties(
	    example_compiled_python_bindings PROPERTIES INSTALL_RPATH "@loader_path/${CMAKE_INSTALL_LIBDIR}")
	else()
	  set_target_properties(example_compiled_python_bindings PROPERTIES INSTALL_RPATH
	                                          "$ORIGIN/${CMAKE_INSTALL_LIBDIR}")
	endif()
	

endif()