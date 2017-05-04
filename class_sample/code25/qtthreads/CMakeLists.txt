cmake_minimum_required(VERSION 3.2)
project(THREAD_EXAMPLES CXX)

# require a C++11 compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core Concurrent)

ADD_EXECUTABLE(qt_concurrent_ex1 qt_concurrent_ex1.cpp)
TARGET_LINK_LIBRARIES(qt_concurrent_ex1 Qt5::Core Qt5::Concurrent)

ADD_EXECUTABLE(qt_concurrent_ex2 qt_concurrent_ex2.cpp)
TARGET_LINK_LIBRARIES(qt_concurrent_ex2 Qt5::Core Qt5::Concurrent)

ADD_EXECUTABLE(qt_concurrent_ex3 qt_concurrent_ex3.cpp)
TARGET_LINK_LIBRARIES(qt_concurrent_ex3 Qt5::Core Qt5::Concurrent)

ADD_EXECUTABLE(qthread_ex1 qthread_ex1.cpp)
TARGET_LINK_LIBRARIES(qthread_ex1 Qt5::Core Qt5::Concurrent)

ADD_EXECUTABLE(qthread_ex2 qthread_ex2.cpp)
TARGET_LINK_LIBRARIES(qthread_ex2 Qt5::Core Qt5::Concurrent)
