cmake_minimum_required(VERSION 3.5)
project(JSONExample CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

add_executable(JSONExample main.cpp student.h student.cpp grade.h grade.cpp)
set_property(TARGET JSONExample PROPERTY CXX_STANDARD 11)
target_link_libraries(JSONExample Qt5::Widgets Qt5::Core)
