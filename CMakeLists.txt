cmake_minimum_required(VERSION 3.20)
project(aicpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0148 NEW)

set(gtest_force_shared_crt on)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

find_package(Boost COMPONENTS headers json REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(include)

set(SRCS src/aicpp/Brain.cpp src/aicpp/Connection.cpp src/aicpp/Neuron.cpp src/aicpp/Hodel.cpp src/aicpp/DslEngine.cpp src/aicpp/DslSystem.cpp)
set(HEADERS include/aicpp/Brain.h include/aicpp/Connection.h include/aicpp/Neuron.h include/aicpp/utility.h include/aicpp/Hodel.h include/aicpp/DslEngine.h include/aicpp/DslSystem.h)

enable_testing()
add_executable(test_aicpp src/test_aicpp.cpp ${SRCS} ${HEADERS})

target_include_directories(test_aicpp PRIVATE include)

if (WIN32)
    target_link_libraries(test_aicpp PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
else()
    target_link_libraries(test_aicpp PRIVATE Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
endif()

add_test(NAME TestAiCpp COMMAND test_aicpp)

if (WIN32)
else()
include(GoogleTest)
gtest_discover_tests(test_aicpp)
endif()
