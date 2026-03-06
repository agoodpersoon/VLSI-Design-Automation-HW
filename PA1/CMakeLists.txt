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
    message(STATUS "GTest include dir found in ${GTest_INCLUDE_DIRS}$")
else()
    message(WARNING "Cannot find GTest!")
endif()

set(SOURCES
    src/parser.cpp
)

# Executable a: PA1 which links against Boost Graph library
add_executable(PA1 main.cpp ${SOURCES})
target_include_directories(PA1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PA1 PRIVATE Boost::graph)

# Executable b: PA1_test which links against GTest and Boost Graph library
add_executable(unit_tests unit_tests/test_graph.cpp)
target_link_libraries(unit_tests PRIVATE Boost::graph GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)