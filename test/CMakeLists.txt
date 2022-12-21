cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

add_executable(test_graph_calc test_graph_calc.cpp)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
target_include_directories(test_graph_calc PUBLIC ${SET_GRAPH_INCLUDE_DIRS} ${GRAPH_CALC_INCLUDE_DIRS})
target_link_libraries(test_graph_calc PUBLIC ${SET_GRAPH_LIBRARIES} ${GRAPH_CALC_LIBRARIES} "-lgcov" GTest::GTest GTest::Main)
