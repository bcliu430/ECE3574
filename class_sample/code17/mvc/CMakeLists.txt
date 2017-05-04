cmake_minimum_required(VERSION 3.2)
project(MVC CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Widgets)

ADD_EXECUTABLE(example1 example1.cpp)
set_property(TARGET example1 PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(example2 example2.cpp)
set_property(TARGET example2 PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(example2 Qt5::Widgets)

ADD_EXECUTABLE(example3 example3.cpp)
set_property(TARGET example3 PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(example3 Qt5::Widgets)
