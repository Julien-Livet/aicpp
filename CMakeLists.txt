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
find_package(dlib REQUIRED)
find_package(Python3 COMPONENTS Development Interpreter REQUIRED)
find_package(pybind11 REQUIRED)

include_directories(include)

set(SRCS src/aicpp/Brain.cpp src/aicpp/Connection.cpp src/aicpp/Neuron.cpp src/aicpp/Hdl.cpp src/aicpp/Hodel.cpp src/aicpp/DslEngine.cpp src/aicpp/DslSystem.cpp)
set(HEADERS include/aicpp/Brain.h include/aicpp/Connection.h include/aicpp/Neuron.h include/aicpp/utility.h include/aicpp/Hdl.h include/aicpp/Hodel.h include/aicpp/DslEngine.h include/aicpp/DslSystem.h)

enable_testing()
add_executable(test_aicpp src/test_aicpp.cpp ${SRCS} ${HEADERS})
add_executable(dsl_dataset src/dsl_dataset.cpp ${SRCS} ${HEADERS})

add_definitions(-DPYBIND11_DETAILED_ERROR_MESSAGES)
pybind11_add_module(aicpppy src/aicpppy.cpp ${SRCS} ${HEADERS})

target_include_directories(test_aicpp PRIVATE include)
target_include_directories(dsl_dataset PRIVATE include)
target_include_directories(aicpppy PRIVATE include)

if (WIN32)
    target_link_libraries(test_aicpp PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen gtest gtest_main dlib::dlib)
    target_link_libraries(dsl_dataset PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen dlib::dlib)
    target_link_libraries(aicpppy PRIVATE Ws2_32 Boost::json Boost::headers Eigen3::Eigen dlib::dlib)
else()
    target_link_libraries(test_aicpp PRIVATE Boost::json Boost::headers Eigen3::Eigen gtest gtest_main dlib::dlib)
    target_link_libraries(dsl_dataset PRIVATE Boost::json Boost::headers Eigen3::Eigen dlib::dlib)
    target_link_libraries(aicpppy PRIVATE Boost::json Boost::headers Eigen3::Eigen dlib::dlib)
endif()

add_test(NAME TestAiCpp COMMAND test_aicpp)

if (WIN32)
else()
include(GoogleTest)
gtest_discover_tests(test_aicpp)
endif()

install(TARGETS aicpppy LIBRARY DESTINATION .)
