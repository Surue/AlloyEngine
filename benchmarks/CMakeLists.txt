include_directories(${GOOGLE_BENCH_DIR}/include)
set_target_properties (benchmark benchmark_main PROPERTIES FOLDER Externals\\GTest)

SET(BENCH_DIR ${CMAKE_SOURCE_DIR}/benchmarks)
file(GLOB BENCH_FILES ${BENCH_DIR}/*.cpp)
include_directories("include/")
foreach(bench_file ${BENCH_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH bench_relative_path ${BENCH_DIR} ${bench_file})
    string( REPLACE ".cpp" "" bench_name ${bench_relative_path} )
    add_executable(${bench_name} ${bench_file})
    # Make sure YourLib is linked to each app
    target_link_libraries(${bench_name} PUBLIC benchmark benchmark_main Alloy_Core Alloy_Common Alloy_Modules )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Oi /Ox /fp:fast /FAs /arch:AVX2")
    
    set_target_properties (${bench_name} PROPERTIES FOLDER Benchmarks)
endforeach()