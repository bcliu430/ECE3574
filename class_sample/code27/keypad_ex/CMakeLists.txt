cmake_minimum_required(VERSION 3.2)
project(KeyPadExample CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt4 REQUIRED QtGui)

ADD_EXECUTABLE(keypad main.cpp)
set_property(TARGET keypad PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(keypad Qt4::QtGui)
