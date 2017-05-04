cmake_minimum_required(VERSION 3.2)
project(basic_type CXX)

add_executable(cpp11_prodcon cpp11_prodcon.cpp)
set_property(TARGET cpp11_prodcon PROPERTY CXX_STANDARD 11)
