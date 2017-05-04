cmake_minimum_required(VERSION 3.2)
project(QProcess_As_Fork CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core Network)
  
ADD_EXECUTABLE(qtipc qprocess_localsocket_comm.cpp)
set_property(TARGET qtipc PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(qtipc Qt5::Core Qt5::Network)
