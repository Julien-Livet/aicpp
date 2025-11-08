cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0167 NEW)
project(ai)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/bigobj)
else()
    add_compile_options(-Wa,-mbig-obj -O3)
endif()

find_package(Boost COMPONENTS headers json REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(ai main.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(ai Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(benchmark_arc-agi benchmark_arc-agi.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(benchmark_arc-agi Ws2_32 Boost::json Boost::headers Eigen3::Eigen)

add_executable(hello_world hello_world.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(hello_world Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai1 test_ai1.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(test_ai1 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai3 test_ai3.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(test_ai3 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_ai5 test_ai5.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(test_ai5 Ws2_32 Boost::headers Eigen3::Eigen)

add_executable(test_learn test_learn.cpp utility.h Brain.cpp Brain.h Connection.cpp Connection.h Neuron.cpp Neuron.h)
target_link_libraries(test_learn Ws2_32 Boost::headers Eigen3::Eigen)
