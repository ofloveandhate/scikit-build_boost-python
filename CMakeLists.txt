cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(example)

include(CMakePrintHelpers) # so we can print cmake variable values

include(GNUInstallDirs)  # so that `CMAKE_INSTALL_LIBDIR` is not blank. eg



find_package(Python 3.13 REQUIRED COMPONENTS Interpreter Development.Module NumPy)

# the core builds a library and an executable depending on that library

add_library(example_core_lib)
add_executable(example_core_exe)

add_subdirectory(core)





# next, in `python_bindings`, build a shared python library, and a pure-python library that wraps around that.

python_add_library(example_compiled_python_bindings MODULE WITH_SOABI) 
set_property(TARGET example_compiled_python_bindings PROPERTY OUTPUT_NAME _example)

add_subdirectory(python_bindings)


# finally, the pure-python part of the project.

add_subdirectory(python_wrapper)
