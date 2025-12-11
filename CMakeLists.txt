cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0167 NEW)
project(aicpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/bigobj)
else()
    add_compile_options(-Wa,-mbig-obj -O3)
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

include_directories(include)

set(SRCS src/Brain.cpp src/Connection.cpp src/Neuron.cpp)
set(HEADERS include/aicpp/Brain.h include/aicpp/Connection.h include/aicpp/Neuron.h include/aicpp/utility.h)

add_executable(ai src/main.cpp ${SRCS} ${HEADERS})
target_link_libraries(ai Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(arc-agi src/arc-agi.cpp ${SRCS} ${HEADERS})
target_link_libraries(arc-agi Ws2_32 Boost::json Boost::headers Eigen3::Eigen)

add_executable(arc-agi_tasks src/arc-agi_tasks.cpp ${SRCS} ${HEADERS})
target_link_libraries(arc-agi_tasks Ws2_32 Boost::json Boost::headers Eigen3::Eigen)

add_executable(benchmark_arc-agi src/benchmark_arc-agi.cpp ${SRCS} ${HEADERS})
target_link_libraries(benchmark_arc-agi Ws2_32 Boost::json Boost::headers Eigen3::Eigen)

add_executable(hello_world src/hello_world.cpp ${SRCS} ${HEADERS})
target_link_libraries(hello_world Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai1 src/test_ai1.cpp ${SRCS} ${HEADERS})
target_link_libraries(test_ai1 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai3 src/test_ai3.cpp ${SRCS} ${HEADERS})
target_link_libraries(test_ai3 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai5 src/test_ai5.cpp ${SRCS} ${HEADERS})
target_link_libraries(test_ai5 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_learn src/test_learn.cpp ${SRCS} ${HEADERS})
target_link_libraries(test_learn Ws2_32 Boost::headers Eigen3::Eigen)

enable_testing()
add_executable(test_arc-agi src/test_arc-agi.cpp ${SRCS} ${HEADERS})
target_link_libraries(test_arc-agi Ws2_32 Boost::json Boost::headers Eigen3::Eigen gtest gtest_main)

add_test(NAME TestArcAgi COMMAND test_arc-agi)

if (WIN32)
else()
include(GoogleTest)
gtest_discover_tests(test_arc-agi)
endif()
