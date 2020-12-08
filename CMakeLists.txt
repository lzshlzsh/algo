cmake_minimum_required(VERSION 3.10)

project(Algo)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(heap_sort heap_sort.cpp)
add_executable(atoi leetcode/atoi.cpp)
add_executable(001-two-sum leetcode/001-two-sum.cpp)

#add_executable(test_cache_coherent test_cache_coherent.cpp)
#target_link_libraries(test_cache_coherent pthread)