cmake_minimum_required(VERSION 3.16)
project(AlloyEngine)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

#Remotery
set(REMOTERY_DIR "externals/Remotery" CACHE STRING "")
add_subdirectory(${REMOTERY_DIR})
include_directories(${REMOTERY_DIR})

#Common
set(ALLOY_COMMON_DIR "${CMAKE_SOURCE_DIR}/engine/common/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_COMMON_DIR})

#Modules
set(ALLOY_MODULES_DIR "${CMAKE_SOURCE_DIR}/engine/modules/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_MODULES_DIR})

#Core
set(ALLOY_CORE_DIR "${CMAKE_SOURCE_DIR}/engine/core/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_CORE_DIR})

#Test
enable_testing()
SET(Alloy_TEST_DIR "${CMAKE_SOURCE_DIR}/test/" CACHE INTERNAL "")
add_subdirectory(${Alloy_TEST_DIR})

set(GOOGLE_TEST_DIR "externals/googletest")
set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(INSTALL_GTEST OFF CACHE INTERNAL "")
add_subdirectory(${GOOGLE_TEST_DIR})
include_directories(${GOOGLE_TEST_DIR}/include)

set_target_properties (gtest PROPERTIES FOLDER Externals/GTest)
set_target_properties(gtest_main PROPERTIES FOLDER Externals/GTest)

#Benchmark
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "")
set(GOOGLE_BENCH_DIR "externals/benchmark" CACHE STRING "")
set(HAVE_STD_REGEX ON CACHE BOOL "")
add_subdirectory(${GOOGLE_BENCH_DIR})
add_subdirectory("benchmarks/")

set_target_properties (benchmark PROPERTIES FOLDER Externals/Benchmarks)
set_target_properties(benchmark_main PROPERTIES FOLDER Externals/Benchmarks)

add_executable(AlloyEngine main.cpp)

target_link_libraries(AlloyEngine PUBLIC Alloy_Core Alloy_Common Alloy_Modules)

