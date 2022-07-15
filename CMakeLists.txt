cmake_minimum_required(VERSION 3.21)
project(HashTable)

set(CMAKE_CXX_STANDARD 11)

add_executable(HashTable main.cpp hashtable.h hashtable.hpp passserver.cpp passserver.h)
