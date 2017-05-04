cmake_minimum_required(VERSION 3.5)
project(SettingsExample CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(callbacks callbacks.cpp)
set_property(TARGET callbacks PROPERTY CXX_STANDARD 11)

add_executable(callbacks_methods callbacks_methods.cpp)
set_property(TARGET callbacks_methods PROPERTY CXX_STANDARD 11)

add_executable(settings qtmain.cpp
  settings.h
  settings_widget.h settings_widget.cpp
  receiver_object.h receiver_object.cpp)
set_property(TARGET settings PROPERTY CXX_STANDARD 11)
target_link_libraries(settings Qt5::Widgets)
