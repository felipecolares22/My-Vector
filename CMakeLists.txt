cmake_minimum_required(VERSION 3.5)
project (my_vector VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Library ===
#Can manually add the sources using the set command as follows:
#set(SOURCES src/filter.cpp src/timing_filter.cpp)

# We want to build a static library.
add_library(my_vector STATIC "test/driver_vector.cpp")

#define C++11 as the standard.
#target_compile_features(iranges PUBLIC cxx_std_11)

set ( APP_SOURCE_DIR "app" )

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS my_vector ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/../${APP_SOURCE_DIR}/lib)

# Also, copy the headers to the include directory of the application.
install(FILES ${CMAKE_SOURCE_DIR}/include/vector.h DESTINATION ${CMAKE_SOURCE_DIR}/../${APP_SOURCE_DIR}/include )

#=== Test target ===

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES_TEST "test/*.cpp")
#
add_executable(vector_tests ${SOURCES_TEST})

# Link with the google test libraries.
target_link_libraries(vector_tests PRIVATE ${GTEST_LIBRARIES} PRIVATE my_vector PRIVATE pthread )

#define C++11 as the standard.
#set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)
#target_compile_features(run_tests PUBLIC cxx_std_11)