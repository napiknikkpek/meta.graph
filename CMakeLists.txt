cmake_minimum_required(VERSION 3.7)

project(meta.graph LANGUAGES CXX)

find_package(Boost 1.63 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_compile_options(-std=c++1z)
add_compile_options(-stdlib=libc++)

set(CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)

add_library(meta.graph INTERFACE)
target_include_directories(meta.graph INTERFACE include)

include_directories(${meta.graph_SOURCE_DIR}/include)

add_subdirectory(example)
add_subdirectory(benchmark)
