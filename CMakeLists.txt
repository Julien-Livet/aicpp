cmake_minimum_required(VERSION 3.20)
project(aicpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    cmake_policy(SET CMP0167 NEW)
endif()

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
find_package(pybind11 REQUIRED)

include_directories(include)

set(SRCS src/aicpp/Brain.cpp src/aicpp/Connection.cpp src/aicpp/Neuron.cpp src/aicpp/primitives.cpp)
set(HEADERS include/aicpp/Brain.h include/aicpp/Connection.h include/aicpp/Neuron.h include/aicpp/partials.h include/aicpp/primitives.h include/aicpp/utility.h)

enable_testing()
add_executable(test_aicpp src/test_aicpp.cpp ${SRCS} ${HEADERS})

add_definitions(-DPYBIND11_DETAILED_ERROR_MESSAGES)
pybind11_add_module(pyaicpp src/python_bindings.cpp ${SRCS} ${HEADERS})

target_include_directories(test_aicpp PRIVATE include)
target_include_directories(pyaicpp PRIVATE include)

if (WIN32)
    target_link_libraries(test_aicpp Ws2_32 Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
    target_link_libraries(pyaicpp PRIVATE Ws2_32 Eigen3::Eigen Boost::headers)
else()
    target_link_libraries(test_aicpp Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)
    target_link_libraries(pyaicpp PRIVATE Eigen3::Eigen Boost::headers)
endif()

install(TARGETS pyaicpp LIBRARY DESTINATION .)

add_test(NAME TestAiCpp COMMAND test_aicpp)

if (WIN32)
else()
include(GoogleTest)
gtest_discover_tests(test_aicpp)
endif()
