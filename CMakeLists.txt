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
find_package(Python3 REQUIRED COMPONENTS Interpreter)

include_directories(include)

set(REGISTER_SCRIPT
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cpp_register.py"
)

set(HODEL_REGISTER
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aicpp/HodelRegister.cpp"
)

set(POLYMORPHIC_REGISTER
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aicpp/PolymorphicNeuronRegister.cpp"
)

file(GLOB REGISTER_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/aicpp/*Neuron.h"
)

add_custom_command(
    OUTPUT
        "${HODEL_REGISTER}"
        "${POLYMORPHIC_REGISTER}"

    COMMAND
        "${Python3_EXECUTABLE}" "${REGISTER_SCRIPT}" Hodel

    DEPENDS
        "${REGISTER_SCRIPT}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/aicpp/Hodel.h"
        ${REGISTER_HEADERS}

    WORKING_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts"

    COMMENT "Generating native and polymorphic neuron registries"
    VERBATIM
)

add_custom_target(generate_registers
    DEPENDS
        "${HODEL_REGISTER}"
        "${POLYMORPHIC_REGISTER}"
)

set(REGISTER_SCRIPT
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cpp_register.py"
)

set(HODEL_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/include/aicpp/Hodel.h"
)

set(HODEL_REGISTER
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aicpp/HodelRegister.cpp"
)

set(POLYMORPHIC_REGISTER
    "${CMAKE_CURRENT_SOURCE_DIR}/src/aicpp/PolymorphicNeuronRegister.cpp"
)

# Discover neuron headers automatically.
file(GLOB POLYMORPHIC_NEURON_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/aicpp/*Neuron.h"
)

add_custom_command(
    OUTPUT
        "${HODEL_REGISTER}"
        "${POLYMORPHIC_REGISTER}"

    COMMAND
        "${Python3_EXECUTABLE}"
        "${REGISTER_SCRIPT}"
        Hodel

    DEPENDS
        "${REGISTER_SCRIPT}"
        "${HODEL_HEADER}"
        ${POLYMORPHIC_NEURON_HEADERS}

    WORKING_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}"

    COMMENT
        "Generating native and polymorphic neuron registries"

    VERBATIM
)

add_custom_target(generate_neuron_registries
    DEPENDS
        "${HODEL_REGISTER}"
        "${POLYMORPHIC_REGISTER}"
)

add_executable(dsl_dataset
               src/dsl_dataset.cpp
               src/aicpp/Hodel.cpp include/aicpp/Hodel.h
               include/aicpp/Neuron.h
               src/aicpp/Connection.cpp include/aicpp/Connection.h
               include/aicpp/DslType.h
               include/aicpp/PolymorphicNeuron.h
               include/aicpp/ComposeNeuron.h
               src/aicpp/ChainNeuron.cpp include/aicpp/ChainNeuron.h
               src/aicpp/ForkNeuron.cpp include/aicpp/ForkNeuron.h
               src/aicpp/ExtractNeuron.cpp include/aicpp/ExtractNeuron.h
                src/aicpp/PolymorphicNeuronRegister.cpp include/aicpp/PolymorphicNeuronRegister.h
                src/aicpp/HodelRegister.cpp include/aicpp/HodelRegister.h
               include/aicpp/FunctionValue.h
               include/aicpp/utility.h)

if(USE_TESTS STREQUAL "TRUE")
    enable_testing()
    add_executable(test_aicpp
                src/test_aicpp.cpp
                src/aicpp/Hodel.cpp include/aicpp/Hodel.h
                include/aicpp/Neuron.h
                src/aicpp/Connection.cpp include/aicpp/Connection.h
                include/aicpp/DslType.h
                include/aicpp/PolymorphicNeuron.h
                include/aicpp/ComposeNeuron.h
                src/aicpp/ChainNeuron.cpp include/aicpp/ChainNeuron.h
                src/aicpp/ForkNeuron.cpp include/aicpp/ForkNeuron.h
                src/aicpp/ExtractNeuron.cpp include/aicpp/ExtractNeuron.h
                src/aicpp/PolymorphicNeuronRegister.cpp include/aicpp/PolymorphicNeuronRegister.h
                src/aicpp/HodelRegister.cpp include/aicpp/HodelRegister.h
                include/aicpp/FunctionValue.h
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
