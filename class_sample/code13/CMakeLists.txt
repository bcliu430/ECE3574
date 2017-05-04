cmake_minimum_required(VERSION 3.5)
project(EventExamples CXX)

add_library(callback STATIC callback_library.h callback_library.cpp)
set_property(TARGET callback PROPERTY CXX_STANDARD 11)

add_executable(callback_example callback_example.cpp)
target_link_libraries(callback_example callback)
set_property(TARGET callback_example PROPERTY CXX_STANDARD 11)


add_library(polymorphic STATIC polymorphic_library.h polymorphic_library.cpp)
set_property(TARGET polymorphic PROPERTY CXX_STANDARD 11)

add_executable(polymorphic_example polymorphic_example.cpp)
target_link_libraries(polymorphic_example polymorphic)
set_property(TARGET polymorphic_example PROPERTY CXX_STANDARD 11)
