# note: use "cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ." to generate debug version for coverage
# Copyright <lwolmer, lshiela, jgerrick> 2022
#############################################################
#                                                           #
#                   GLOBAL CMAKE SETUP                      #
#                                                           #
#############################################################
cmake_minimum_required(VERSION 3.5)
project(A2_SimpleNavigator)
MESSAGE("${ENABLE_CODE_COVERAGE} before option")
option(ENABLE_CODE_COVERAGE "Add code coverage targets" ON)
MESSAGE("${ENABLE_CODE_COVERAGE} after option")
option(ENABLE_CODE_ANALYSIS "Run cppcheck for code" ON)
# Path to cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
# disable extentions for pure C++
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()
enable_language(CXX)
if(ENABLE_CODE_COVERAGE)
    include(CodeCoverage)
    MESSAGE("${ENABLE_CODE_COVERAGE} after include")
endif()
if(NOT MEMORYCHECK_COMMAND)
    MESSAGE(WARNING "Memory testing tool is not found. Memory testing targets won't be added.")
endif()
if(ENABLE_CODE_ANALYSIS)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        list(
            APPEND CMAKE_CXX_CPPCHECK 
                "--enable=warning"
                "--inconclusive"
                "--force" 
                "--inline-suppr"
                "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
        )
    else()
        MESSAGE(WARNING "CppCheck not found. Continuing without code analysis...")
    endif()
endif(ENABLE_CODE_ANALYSIS)

#############################################################
#                                                           #
#                     GTEST COMPILE                         #
#                                                           #
#############################################################
message("-- Added GTest target from source")
if (NOT TARGET gtest_main)
    unset(CMAKE_CXX_FLAGS)
    unset(CMAKE_CXX_FLAGS_DEBUG)
    set(_flag_sync_required TRUE)
    add_subdirectory(googletest EXCLUDE_FROM_ALL)
    set(GTEST_FOUND TRUE)
endif ()

#############################################################
#                                                           #
#                     Dependencies                          #
#                                                           #
#############################################################
IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/containers)
    add_subdirectory(containers)
ENDIF()

IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/s21_graph)
    add_subdirectory(s21_graph)
ENDIF()

IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/s21_graph_algorithms)
    add_subdirectory(s21_graph_algorithms)
ENDIF()

#############################################################
#                                                              #
#                    additional checks                      #
#                                                           #
#############################################################
find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
        MESSAGE(WARNING ".clang-format file should be placed in src folder, continuing without it, test result may be incorect.")
    else()
        file(GLOB_RECURSE STYLE_CHECK_FILES *.cc *.h *.tpp *.inc)
        list(FILTER STYLE_CHECK_FILES EXCLUDE REGEX "/googletest/")
        add_custom_target(stylecheck
        COMMAND ${CLANG_FORMAT} -n ${STYLE_CHECK_FILES}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

        add_custom_target(stylechange
        COMMAND ${CLANG_FORMAT} -i ${STYLE_CHECK_FILES}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    endif()
    
endif()

#############################################################
#                                                           #
#                          MISC                             #
#                                                           #
#############################################################
#tests
add_custom_target(tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose
                  DEPENDS graph_algorithms_tests graph_tests)

