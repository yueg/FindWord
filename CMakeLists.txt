cmake_minimum_required(VERSION 3.2)
project(FindWord)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(FindWord ${SOURCE_FILES} searchTerm.h searchTerm.cpp simpleDic.h simpleDic.cpp tl_codetbl.h tl_codetbl.cpp Utility.h Utility.cpp countWord.h countWord.cpp)