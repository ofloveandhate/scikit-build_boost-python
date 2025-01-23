cmake_minimum_required(VERSION 3.22)
project(example_compiled_python_bindings)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePrintHelpers) # so we can print cmake variable values

find_package(Python 3.13 REQUIRED COMPONENTS Interpreter Development.Module NumPy)  

find_package(Boost COMPONENTS system python3 REQUIRED)


if (PROJECT_IS_TOP_LEVEL)
    find_package(example REQUIRED CONFIG)


# code to inspect the values of variables, so we can find the ones that are made by the above call.
# see https://stackoverflow.com/questions/49858267/with-find-package-how-do-i-know-which-variables-have-to-be-used-for-linking
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()

    include_directories(${exampleINCLUDES})
endif()










include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})



# list the sources

set(SOURCES
	src/example_pycpp.cpp
)

set(HEADERS
	include/example_pycpp.hpp
)


if(PROJECT_IS_TOP_LEVEL)
    python_add_library(example_compiled_python_bindings MODULE WITH_SOABI) 
    set_property(TARGET example_compiled_python_bindings PROPERTY OUTPUT_NAME _example)
endif()


target_include_directories(example_compiled_python_bindings PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
    )

target_sources(example_compiled_python_bindings PUBLIC ${SOURCES} ${HEADERS})

if(PROJECT_IS_TOP_LEVEL)
	target_link_libraries(example_compiled_python_bindings PRIVATE ${Boost_LIBRARIES} ${exampleLIBDIR})
else()
	target_link_libraries(example_compiled_python_bindings PRIVATE ${Boost_LIBRARIES} example_core_lib)
endif()

# trying to get it to install to the correct directory
# https://stackoverflow.com/questions/1242904/finding-python-site-packages-directory-with-cmake

# https://github.com/scikit-build/scikit-build-sample-projects/blob/main/projects/hello-cmake-package/CMakeLists.txt


if(${SKBUILD})
	install(TARGETS example_compiled_python_bindings LIBRARY DESTINATION .)
else()
	install(TARGETS example_compiled_python_bindings LIBRARY DESTINATION ${Python_SITELIB}/bertini)
endif()


