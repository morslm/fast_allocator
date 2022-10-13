cmake_minimum_required(VERSION 3.11)

project(fast_allocator)

add_subdirectory(allocator)
add_subdirectory(factory)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} allocator factory)