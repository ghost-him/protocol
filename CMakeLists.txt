cmake_minimum_required(VERSION 3.26)
project(program)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(protocol pro)

add_executable(program main.cpp ${pro})
