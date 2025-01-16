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



install(TARGETS example_compiled_python_bindings LIBRARY DESTINATION .)

