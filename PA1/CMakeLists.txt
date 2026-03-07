cmake_minimum_required(VERSION 3.10)
project(PA1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set policy to suppress CMP0167 warning about FindBoost module
cmake_policy(SET CMP0167 NEW)

# Find Boost headers and graph library
find_package(Boost REQUIRED COMPONENTS graph)

# Check if Boost was found and print the include directory
if(Boost_FOUND)
    message(STATUS "Boost include dir found in ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Find GTest headers and libraries
find_package(GTest REQUIRED)

# Check if GTest was found and print the include directory
if(GTest_FOUND)
    message(STATUS "GTest include dir found in ${GTest_INCLUDE_DIRS}")
else()
    message(WARNING "Cannot find GTest!")
endif()

# Set the binary output directory for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define a static library for PA1 sources because both the main executable
# and the test executable will use link against these sources.
file(GLOB PA1_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(PA1_lib STATIC ${PA1_SOURCES})
target_include_directories(PA1_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PA1_lib PUBLIC Boost::graph)

# Executable a: PA1 which links against the project library PA1_lib
# (which in turn links against Boost::graph because of public linkage).
# Note that PA1 itself does not directly link against Boost::graph,
# but it can still use the graph library through PA1_lib.
add_executable(PA1 main.cpp)
target_link_libraries(PA1 PRIVATE PA1_lib)

# Executables b: PA1_test which links against the project library PA1_lib and GTest libraries.
# Note each test source file will be compiled into a separate test executable.
include(GoogleTest)
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE) # Get the filename without extension
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE PA1_lib GTest::gtest GTest::gtest_main)
    gtest_discover_tests(${TEST_NAME})
endforeach()

