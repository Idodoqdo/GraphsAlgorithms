# note: use "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ." to generate debug version for coverage
# Copyright <lwolmer> 2022
#############################################################
#                                                           #
#                         TESTING                           #
#                                                           #
#############################################################
if (GTEST_FOUND)
    cmake_minimum_required(VERSION 3.5)
    project(graph_algorithms_tests LANGUAGES CXX)
    set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
    set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
    if (NOT ${GMockSrc} STREQUAL "")
        list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
        list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
    endif ()

    include_directories(${GTestIncludes})

    set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -g ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS_DEBUG}")
    option(CodeCoverage "CodeCoverage" ON)
    include(CTest)
    file(GLOB TEST_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/../*.cc"
    )
    add_executable(${PROJECT_NAME} ${TEST_SRC})
    configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
    include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../ ${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)
    
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${PROJECT_NAME} PROPERTY THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        gtest
        stdc++
        m
        gtest_main
        Threads::Threads
        s21_graph_algorithms.a
        s21_graph.a
        s21_containers
    )

    set_property(
        TARGET ${PROJECT_NAME}
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}/Temporary ${CMAKE_BINARY_DIR}/Testing ${CMAKE_BINARY_DIR}/TAG ${CMAKE_CURRENT_BINARY_DIR}/coverage ${TEST_CLEAN_FILES}
    )
    add_test(UNIT_TESTS ${PROJECT_NAME})
endif()

#############################################################
#                                                           #
#                        COVERAGE                           #
#                                                           #
#############################################################

if (GTEST_FOUND)
  if (CodeCoverage MATCHES ON)
      include(CodeCoverage)
      setup_target_for_coverage(${PROJECT_NAME}_coverage ${PROJECT_NAME} ${PROJECT_NAME}_coverage)
      set_property(
          TARGET ${PROJECT_NAME}_coverage
          APPEND
          PROPERTY ADDITIONAL_CLEAN_FILES DartConfiguration.tcl
      )
  endif()
    
endif()

#############################################################
#                                                           #
#                    additional checks                      #
#                                                           #
#############################################################
if (GTEST_FOUND)
        add_custom_target(${PROJECT_NAME}_memcheck
            COMMAND CK_FORK=no leaks --atExit --  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
        add_dependencies(${PROJECT_NAME}_memcheck ${PROJECT_NAME})

    # Proper way but there are still reachable blocks
    # add_custom_target(memcheck
    #     COMMAND ${CMAKE_CTEST_COMMAND}
    #         --force-new-ctest-process --test-action memcheck
    #     COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    #     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()
