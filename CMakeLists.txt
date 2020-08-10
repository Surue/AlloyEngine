cmake_minimum_required(VERSION 3.16)
project(AlloyEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlloyEngine main.cpp)

#SFML

# If must link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

# In most cases better set in the CMake cache
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(AlloyEngine sfml-system sfml-window sfml-graphics sfml-audio)