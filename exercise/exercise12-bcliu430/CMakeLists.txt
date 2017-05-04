cmake_minimum_required(VERSION 3.5)
project(Ex12 CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRRENT_DIR ON)
set(CMAKE_PREFIX_PATH $ENV/home/beichen/Qt5.8.0/5.8/gcc_64)

find_package(Qt5Widgets REQUIRED)

add_executable(ex12 main.cpp complex_widget.h complex_widget.cpp)
set(TARGET ex12 PROPERTY CXX_STANDARD 11)
target_link_libraries(ex12 Qt5::Widgets)
