cmake_minimum_required(VERSION 3.10)
project(distributed_k_means)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    ${PROJECT_SOURCE_DIR}/include
)


add_library(lib
    src/algorithms.cpp
    src/geometry.cpp
    src/utils.cpp
    src/sample.cpp
)

add_executable(main src/main.cpp)
target_link_libraries(main lib)