cmake_minimum_required(VERSION 3.16)
project(AlloyEngine)

set(CMAKE_CXX_STANDARD 17)

#Options
option(VULKAN_USE "Use Vulkan as the graphics API" ON)
option(SDL2_USE "Use SDL2 as the window and input library" ON)

#Define macro
if(USE_SDL2)
	add_compile_definitions(USE_SDL2=1)
endif()

#Core
set(ALLOY_CORE_DIR "${CMAKE_SOURCE_DIR}/engine/core/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_CORE_DIR})

#Common
set(ALLOY_COMMON_DIR "${CMAKE_SOURCE_DIR}/engine/common/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_COMMON_DIR})

#Wrappers
set(ALLOY_WRAPPERS_DIR "${CMAKE_SOURCE_DIR}/engine/wrappers/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_WRAPPERS_DIR})

#Modules
set(ALLOY_MODULES_DIR "${CMAKE_SOURCE_DIR}/engine/modules/" CACHE INTERNAL "")
add_subdirectory(${ALLOY_MODULES_DIR})

#Find Vulkan sdk
find_package(Vulkan REQUIRED)

#Find Vulkan sdk
add_executable(AlloyEngine main.cpp)
target_include_directories(AlloyEngine PUBLIC ${VULKAN_INCLUDE_DIRS})
target_link_libraries(AlloyEngine PRIVATE Vulkan::Vulkan PUBLIC Alloy_Core Alloy_Common Alloy_Modules)