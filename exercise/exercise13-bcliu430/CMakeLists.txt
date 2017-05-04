cmake_minimum_required(VERSION 3.5)
project(WidgetEvent CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH $ENV/home/beichen/Qt5.8.0/5.8/gcc_64)
find_package(Qt5Widgets REQUIRED)

add_executable(widget_event main.cpp widget_event.cpp widget_event.hpp)
target_link_libraries(widget_event Qt5::Widgets)
