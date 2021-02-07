#source files
file(GLOB_RECURSE Alloy_DEBUG_SRC debug/src/*.cpp debug/include/*.h)
file(GLOB_RECURSE Alloy_JOB_SYSTEM_SRC job_system/src/*.cpp job_system/include/*.h)
file(GLOB_RECURSE Alloy_MATH_SRC mathematics/src/*.cpp mathematics/include/*.h)
file(GLOB_RECURSE Alloy_PATTERN_SRC patterns/src/*.cpp patterns/include/*.h)
file(GLOB_RECURSE Alloy_TIME_SRC times/src/*.cpp times/include/*.h)
file(GLOB_RECURSE Alloy_UTIL_SRC utils/src/*.cpp utils/include/*.h)

source_group("Debug" FILES ${Alloy_DEBUG_SRC})
source_group("JobSystem" FILES ${Alloy_JOB_SYSTEM_SRC})
source_group("Maths" FILES ${Alloy_MATH_SRC})
source_group("Patterns" FILES ${Alloy_PATTERN_SRC})
source_group("Times" FILES ${Alloy_TIME_SRC})
source_group("Utils" FILES ${Alloy_UTIL_SRC})

List(APPEND Alloy_SRC
		${Alloy_DEBUG_SRC}
		${Alloy_JOB_SYSTEM_SRC}
        ${Alloy_MATH_SRC}
		${Alloy_PATTERN_SRC}
		${Alloy_TIME_SRC}
		${Alloy_UTIL_SRC}
        )

add_library(Alloy_Common STATIC ${Alloy_SRC})

target_link_libraries(Alloy_Common Remotery)
set_target_properties (Alloy_Common PROPERTIES FOLDER Alloy)

target_include_directories(Alloy_Common PUBLIC "debug/include/")
target_include_directories(Alloy_Common PUBLIC "job_system/include/")
target_include_directories(Alloy_Common PUBLIC "mathematics/include/")
target_include_directories(Alloy_Common PUBLIC "patterns/include/")
target_include_directories(Alloy_Common PUBLIC "times/include/")
target_include_directories(Alloy_Common PUBLIC "utils/include/")

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

alloy_lib_config(Alloy_Common)

