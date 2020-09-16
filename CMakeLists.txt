cmake_minimum_required(VERSION 3.16)
project(AlloyEngine)

set(CMAKE_CXX_STANDARD 17)

#Core
set(ALLOY_CORE_DIR "${CMAKE_SOURCE_DIR}/engine/core/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_CORE_DIR})

#Common
set(ALLOY_COMMON_DIR "${CMAKE_SOURCE_DIR}/engine/common/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_COMMON_DIR})

#Modules
set(ALLOY_MODULES_DIR "${CMAKE_SOURCE_DIR}/engine/modules/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_MODULES_DIR})

#SDL2.0
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(AlloyEngine main.cpp)

target_link_libraries(AlloyEngine PRIVATE ${SDL2_LIBRARIES} PUBLIC Alloy_Core Alloy_Common Alloy_Modules)