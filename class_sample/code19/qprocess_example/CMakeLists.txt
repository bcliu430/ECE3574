cmake_minimum_required(VERSION 3.2)
project(QProcess_As_Fork CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core)
  
ADD_EXECUTABLE(qtfork qprocess_as_fork.cpp)
set_property(TARGET qtfork PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(qtfork Qt5::Core)
