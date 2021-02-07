file(GLOB TEST_FILES ${Alloy_TEST_DIR}/*.cpp)
add_executable(Alloy_TEST ${TEST_FILES})

include_directories(${Alloy_CORE_DIR}/include)

target_link_libraries(Alloy_TEST Remotery gtest gtest_main Alloy_Core Alloy_Common Alloy_Modules)

set_target_properties (Alloy_TEST PROPERTIES FOLDER Alloy)