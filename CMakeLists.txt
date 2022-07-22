cmake_minimum_required(VERSION 3.21)
project(projectThree)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp) 

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
add_executable(projectThree ${SOURCE_FILES}) #${SOURCE_FILES} replaced main.cpp as it was set above
target_link_libraries(projectThree PUBLIC Python3::Python)

target_compile_definitions(projectThree PUBLIC -DPROJECT_DIRECTORY="${CMAKE_SOURCE_DIR}") #test
