# note: use "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ." to generate debug version for coverage
#############################################################
#                                                           #
#                   GLOBAL CMAKE SETUP                      #
#                                                           #
#############################################################
option(ENABLE_CODE_ANALYSIS "Run cppcheck for code" ON)
cmake_minimum_required(VERSION 3.13)
# disable extentions for pure C++
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()
enable_language(CXX)

#############################################################
#                                                           #
#                         LIBRARY                           #
#                                                           #
#############################################################
project(s21_containers VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS_DEBUG}")
file(GLOB SRC
     "*.cc"
)
add_library(s21_containers INTERFACE ${SRC})
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

find_package( Boost 1.72.0 COMPONENTS thread )

if ( Boost_FOUND )
    target_compile_definitions(s21_containers INTERFACE BOOST_FOUND)
    target_include_directories( s21_containers INTERFACE ${Boost_INCLUDE_DIRS} )
    target_link_libraries( s21_containers INTERFACE ${Boost_LIBRARIES} )
else()
    message( WARNING "Required Boost packages not found. Compiling without tree print support. Perhaps add -DBOOST_ROOT?" )
endif()
target_include_directories(s21_containers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#############################################################
#                                                           #
#                         TESTING                           #
#                                                           #
#############################################################
if (GTEST_FOUND)
    set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -g ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo ${CMAKE_CXX_FLAGS_DEBUG}")
    project(containers_tests VERSION 1.0 LANGUAGES CXX)
    file(GLOB TEST_SRC
        "tests/*.cc"
    )
    add_executable(containers_tests ${TEST_SRC})
    set_property(TARGET containers_tests PROPERTY CXX_STANDARD 17)
    set_property(TARGET containers_tests PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)

    set_property(TARGET containers_tests PROPERTY THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(containers_tests
        gtest
        stdc++
        m
        gtest_main
        s21_containers
        Threads::Threads
    )

    file(GLOB TEST_CLEAN_FILES
        "*.dot"
    )
    set_property(
        TARGET containers_tests
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES Temporary Testing TAG coverage ${TEST_CLEAN_FILES}
    )
    add_test(UNIT_TESTS containers_tests)
endif()

#############################################################
#                                                           #
#                        COVERAGE                           #
#                                                           #
#############################################################

if (GTEST_FOUND)
    if (ENABLE_CODE_COVERAGE MATCHES ON)
        setup_target_for_coverage(containers_coverage containers_tests containers_coverage)
        set_property(
            TARGET containers_coverage
            APPEND
            PROPERTY ADDITIONAL_CLEAN_FILES DartConfiguration.tcl
        )
    endif()
    
endif()