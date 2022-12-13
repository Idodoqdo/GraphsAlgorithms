# Copyright <lwolmer, lshiela, jgerrick> 2022
cmake_minimum_required(VERSION 3.5)

project(s21_graph_algorithms.a LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -g ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES "*.cc")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC s21_graph.a)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#############################################################
#                                                           #
#                         TESTING                           #
#                                                           #
#############################################################
if (GTEST_FOUND)
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
        add_subdirectory(tests)
    endif()
endif()