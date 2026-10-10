cmake_minimum_required(VERSION 3.20)
project(aicpp)

option(WITHOUT_HODEL_TASKS "Do not use Hodel tasks" OFF)

if(WITHOUT_HODEL_TASKS)
    add_definitions(-DWITHOUT_HODEL_TASKS)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt on)

set(USE_TESTS "FALSE" CACHE STRING "Enable or disable tests")

if(USE_TESTS STREQUAL "TRUE")
    include(FetchContent)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest)
endif()

find_package(Boost COMPONENTS headers json REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(include)

add_executable(dsl_dataset
               src/dsl_dataset.cpp
               src/aicpp/Hodel.cpp include/aicpp/Hodel.h
               src/aicpp/Neuron.cpp include/aicpp/Neuron.h
               src/aicpp/Connection.cpp include/aicpp/Connection.h
               include/aicpp/utility.h)

if(USE_TESTS STREQUAL "TRUE")
    enable_testing()
    add_executable(test_aicpp
                src/test_aicpp.cpp
                src/aicpp/Hodel.cpp include/aicpp/Hodel.h
                src/aicpp/Neuron.cpp include/aicpp/Neuron.h
                src/aicpp/Connection.cpp include/aicpp/Connection.h
                include/aicpp/utility.h)
endif()

if(USE_TESTS STREQUAL "TRUE")
    target_include_directories(test_aicpp PRIVATE include)
endif()

target_include_directories(dsl_dataset PRIVATE include)

if (WIN32)
    if(USE_TESTS STREQUAL "TRUE")
        target_link_libraries(test_aicpp PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
    endif()

    target_link_libraries(dsl_dataset PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen)
else()
    if(USE_TESTS STREQUAL "TRUE")
        target_link_libraries(test_aicpp PRIVATE Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
    endif()

    target_link_libraries(dsl_dataset PRIVATE Boost::json Boost::headers Eigen3::Eigen)
endif()

if(USE_TESTS STREQUAL "TRUE")
    add_test(NAME TestAiCpp COMMAND test_aicpp)

    if (WIN32)
    else()
    include(GoogleTest)
    gtest_discover_tests(test_aicpp)
    endif()
endif()
