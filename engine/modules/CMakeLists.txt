#source files
file(GLOB_RECURSE Alloy_GRAPHICS_SRC graphics/src/*.cpp graphics/include/*.h)
file(GLOB_RECURSE Alloy_PHYSICS_SRC physics/src/*.cpp physics/include/*.h)

source_group("Graphics" FILES ${Alloy_GRAPHICS_SRC})
source_group("Physics" FILES ${Alloy_PHYSICS_SRC})

List(APPEND Alloy_SRC
        ${Alloy_GRAPHICS_SRC}
        ${Alloy_PHYSICS_SRC})

add_library(Alloy_Modules STATIC ${Alloy_SRC})

set_target_properties (Alloy_Modules PROPERTIES FOLDER Alloy/Modules)

target_include_directories(Alloy_Modules PUBLIC "physics/include/")
target_include_directories(Alloy_Modules PUBLIC "graphics/include/")

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

alloy_lib_config(Alloy_Modules)
