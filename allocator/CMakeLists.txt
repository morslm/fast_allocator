cmake_minimum_required(VERSION 3.11)

project(allocator)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
INTERFACE
  ${PROJECT_SOURCE_DIR}/
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
