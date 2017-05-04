cmake_minimum_required(VERSION 3.5)
project(QtTestEx CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets Test REQUIRED)

add_executable(mytest mytest.cpp)
target_link_libraries(mytest Qt5::Test)

add_executable(test_example_widget
  test_example_widget.cpp
  example_widget.h example_widget.cpp)
target_link_libraries(test_example_widget Qt5::Widgets Qt5::Test)

add_executable(exampleapp example_app.cpp example_widget.h example_widget.cpp)
target_link_libraries(exampleapp Qt5::Widgets)

enable_testing()
add_test(mytest mytest)
add_test(test_example test_example_widget)
