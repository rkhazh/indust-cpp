cmake_minimum_required(VERSION 3.0.0)

project(graph_sum_calc)

add_executable(${PROJECT_NAME} main.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

SET(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS})

add_subdirectory(set_graph_lib)
add_subdirectory(graph_calc_lib)

SET_TARGET_PROPERTIES(graph_sum_calc PROPERTIES LINKER_LANGUAGE CXX)

#add_library(matrix_lib INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC ${GRAPH_CALC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GRAPH_CALC_LIBRARIES})

#add_subdirectory(test)