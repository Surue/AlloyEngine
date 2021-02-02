#source files
file(GLOB_RECURSE Alloy_GRAPHICS_SRC graphics/src/*.cpp graphics/include/*.h)
file(GLOB_RECURSE Alloy_INPUTS_SRC inputs/src/*.cpp inputs/include/*.h)
file(GLOB_RECURSE Alloy_PHYSICS_SRC physics/src/*.cpp physics/include/*.h)

List(APPEND Alloy_SRC
        ${Alloy_GRAPHICS_SRC}
		${Alloy_INPUTS_SRC}
        ${Alloy_PHYSICS_SRC})

add_library(Alloy_Modules STATIC ${Alloy_SRC})

set_target_properties (Alloy_Modules PROPERTIES FOLDER Alloy)
#SFML

# If must link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# In most cases better set in the CMake cache
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(Alloy_Modules PUBLIC sfml-system sfml-window sfml-graphics sfml-audio PUBLIC Alloy_Common)

target_include_directories(Alloy_Modules PUBLIC "graphics/include/")
target_include_directories(Alloy_Modules PUBLIC "inputs/include/")
target_include_directories(Alloy_Modules PUBLIC "physics/include/")

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

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

assign_source_group(${Alloy_SRC})
