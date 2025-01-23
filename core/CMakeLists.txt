# this is the cmake file for the core
#
# it builds two things:
# * the core library
# * a command line executable
#
# this should be buildable without needing to build the python part at all.


cmake_minimum_required(VERSION 3.22) 
project(
    example_core_lib
    VERSION "0.0.0"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakePrintHelpers) # so we can print cmake variable values

# In order to find conda, run 'conda activate' and then use 'cmake .. -DCMAKE_PREFIX_PATH=$CONDA_PREFIX' when cmaking

# All source files to be compiled
# We can either explicitly list all files or use glob, 
# we chose to explicitly list files and not to glob
#file(GLOB SOURCES src/*.cpp)


cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC")

# since i don't want to duplicate cmake files across components of this
# large project, they live a level up.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")


# the "real" package this example models uses all these libraries, 
# so i'm leaving them here

find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(MPC REQUIRED)

include_directories(${GMP_INCLUDES})
include_directories(${MPC_INCLUDES})


# the "real" package this example models uses all these boost tools, 
# so i'm leaving them here
find_package(Boost 1.82 REQUIRED
                COMPONENTS 
                    serialization
                    unit_test_framework
                    filesystem
                    system
                    chrono
                    regex
                    timer
                    log
                    thread
                    log_setup
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)





##############
#
# Specify how to build the library
#
#####################



set(EXAMPLE_CORE_HEADERS 
    include/example/core.hpp
)


set(EXAMPLE_CORE_SOURCES 
    src/core.cpp 
)



set(REQUIRED_EXTERNAL_LIBRARIES
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    ${MPC_LIBRARIES}
    Eigen3::Eigen
    ${Boost_LIBRARIES}
)




if(PROJECT_IS_TOP_LEVEL)
    add_library(example_core_lib)
endif()



target_sources(example_core_lib PRIVATE
    ${EXAMPLE_CORE_HEADERS}
    ${EXAMPLE_CORE_SOURCES}
)

# see https://stackoverflow.com/questions/25676277/cmake-target-include-directories-prints-an-error-when-i-try-to-add-the-source
# for more on these generator expressions, $<INSTALL_INTERFACE, etc.

target_include_directories(example_core_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>  # <prefix>/include
    )

# target_include_directories(example_core_lib PUBLIC $<INSTALL_INTERFACE:include>)

target_link_libraries(example_core_lib PUBLIC ${REQUIRED_EXTERNAL_LIBRARIES})

install( 
    TARGETS example_core_lib
    EXPORT exampleTargets  # this name should match the name below where we generate the cmake files for finding the package
    # ARCHIVE DESTINATION "lib"
    # LIBRARY DESTINATION "lib"
    # COMPONENT library
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
) 


install(
    FILES ${EXAMPLE_CORE_HEADERS}
    DESTINATION "include/example/"
)





############
#
#  cmake install files, so other packages can find the core
#
####

# see https://github.com/scikit-build/scikit-build-sample-projects/blob/main/projects/hello-cmake-package/CMakeLists.txt
# for my sources for doing this part

# also, see https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html.  
# and https://iamsorush.com/posts/cpp-cmake-config/

# this cmake include gives us access to CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)  # https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html

set(EXAMPLE_CMAKE_PACKAGE_INSTALL_SUBDIR "share/example/cmake")
set(SYSCONFIG_INSTALL_DIR ${CMAKE_INSTALL_SYSCONFDIR}
    CACHE PATH "Location of configuration files" )

install(
  EXPORT exampleTargets  # this name before Targets should match the name of the variable set above in a previous install call
  NAMESPACE example::
  DESTINATION ${EXAMPLE_CMAKE_PACKAGE_INSTALL_SUBDIR})

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  exampleConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})  #set so we can use in configure_package_config_file()
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}) # ditto

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/../cmake/exampleConfig.cmake.in" exampleConfig.cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR LIB_INSTALL_DIR
  INSTALL_DESTINATION ${EXAMPLE_CMAKE_PACKAGE_INSTALL_SUBDIR}
  )

install(FILES "${PROJECT_BINARY_DIR}/exampleConfig.cmake"
              "${PROJECT_BINARY_DIR}/exampleConfigVersion.cmake"
        DESTINATION ${EXAMPLE_CMAKE_PACKAGE_INSTALL_SUBDIR})









##############################
#
# now stuff for the executable
#
##############################

set(EXAMPLE_EXECUTABLE_SOURCES 
    src/executable.cpp 
)

set(EXAMPLE_EXECUTABLE_HEADERS 
    include/example/executable.hpp
)


if(PROJECT_IS_TOP_LEVEL)
    add_executable(example_core_exe)
endif()

target_sources(example_core_exe PRIVATE ${EXAMPLE_EXECUTABLE_SOURCES} ${EXAMPLE_EXECUTABLE_HEADERS})

target_link_libraries(example_core_exe example_core_lib)




install( 
    TARGETS example_core_exe
    ARCHIVE DESTINATION "bin"
    COMPONENT executable
) 













###########################################
#
# set up some things for unit testing, which uses Boost.Unittest
#
##################################

# TODO make this conditional on wanting them actually built.
# see https://github.com/bertiniteam/b2/issues/202

set(EXAMPLE_CORE_TEST_SOURCES
    test/test_core.cpp 
)

add_executable(test_core ${EXAMPLE_CORE_TEST_SOURCES})
target_include_directories(test_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test)

target_link_libraries(test_core ${Boost_LIBRARIES} example_core_lib)
add_test(NAME test_core COMMAND ${CMAKE_BINARY_DIR}/test_core)



enable_testing()




