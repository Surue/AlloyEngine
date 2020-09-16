set_property(GLOBAL PROPERTY USE_FOLDERS On)

#VULKAN
#source files
file(GLOB_RECURSE Alloy_VULKAN_DEVICES_SRC vulkan/src/devices/*.cpp vulkan/include/devices/*.h)

source_group("Vulkan/Devices" FILES ${Alloy_VULKAN_DEVICES_SRC})

add_library(Vulkan_Wrapper STATIC ${Alloy_VULKAN_DEVICES_SRC})

#Find Vulkan sdk
find_package(Vulkan REQUIRED)

set_target_properties (Vulkan_Wrapper PROPERTIES FOLDER wrappers)
target_include_directories(Vulkan_Wrapper PUBLIC "vulkan/include/" ${VULKAN_INCLUDE_DIRS})
target_link_libraries(Vulkan_Wrapper PRIVATE Vulkan::Vulkan)

#SDL
#source files
file(GLOB_RECURSE Alloy_SDL_SRC sdl/src/*.cpp sdl/include/*.h)

source_group("SDL" FILES ${Alloy_SDL_SRC})

add_library(SDL_Wrapper STATIC ${Alloy_SDL_SRC})

set_target_properties (SDL_Wrapper PROPERTIES FOLDER wrappers)

#Find SDL 2.0
find_package(SDL2 REQUIRED)

target_include_directories(SDL_Wrapper PUBLIC "sdl/include/" ${SDL2_INCLUDE_DIRS})
target_link_libraries(SDL_Wrapper PUBLIC ${SDL2_LIBRARIES})

function(alloy_lib_config library)
    #warning flags
    target_compile_options(${library} PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -Wall -Wextra>
            $<$<CXX_COMPILER_ID:MSVC>:
            /W4>)
    set_target_properties(${library} PROPERTIES UNITY_BUILD ON)
    if(MSVC)
        set_target_properties(${library} PROPERTIES COMPILE_FLAGS " /arch:AVX2 /Oi ")
    elseif(UNIX)
        set_property(TARGET ${library} APPEND_STRING PROPERTY CMAKE_CXX_FLAGS_DEBUG "-fno-rtti -fno-exceptions -Wall -Wextra")
        set_property(TARGET ${library} APPEND_STRING PROPERTY CMAKE_CXX_FLAGS_RELEASE "-fno-rtti -fno-exceptions -Wall -Wextra")
        if(ARM)
            set_property(TARGET ${library} APPEND_STRING PROPERTY COMPILE_FLAGS "-march=native -mfpu=neon ")
        else()
            set_property(TARGET ${library} APPEND_STRING PROPERTY COMPILE_FLAGS "-march=haswell ")
        endif()
    endif()
endfunction()

alloy_lib_config(Vulkan_Wrapper)
alloy_lib_config(SDL_Wrapper)

