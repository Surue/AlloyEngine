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

#Wrappers
set(ALLOY_WRAPPERS_DIR "${CMAKE_SOURCE_DIR}/engine/wrappers/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_WRAPPERS_DIR})

#Find Vulkan sdk
find_package(Vulkan REQUIRED)

add_executable(AlloyEngine main.cpp)
target_include_directories(AlloyEngine PUBLIC ${VULKAN_INCLUDE_DIRS})
target_link_libraries(AlloyEngine PRIVATE Vulkan::Vulkan PUBLIC Alloy_Core Alloy_Common Alloy_Modules SDL_Wrapper Vulkan_Wrapper)