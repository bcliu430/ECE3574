cmake_minimum_required(VERSION 3.5)
project(QtSharedDeque CXX)

# require a C++11 compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
find_package(Qt5 COMPONENTS Core REQUIRED)
  
ADD_EXECUTABLE(qt_shared_deque_1 qt_shared_deque_1.cpp shared_ring_buffer.h shared_ring_buffer.tpp )
TARGET_LINK_LIBRARIES(qt_shared_deque_1 Qt5::Core)

ADD_EXECUTABLE(qt_shared_deque_2 qt_shared_deque_2.cpp shared_ring_buffer.h shared_ring_buffer.tpp )
TARGET_LINK_LIBRARIES(qt_shared_deque_2 Qt5::Core)
