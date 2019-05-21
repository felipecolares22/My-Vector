cmake_minimum_required(VERSION 3.5)
project (vector VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 14)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include )

#=== Main App ===
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "test/*.cpp")

add_executable(vector_tests ${SOURCES})