cmake_minimum_required(VERSION 2.8)
project(impl CXX)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions( -D_OS_OSX )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_definitions( -D_OS_WINDOWS )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_definitions( -D_OS_LINUX )
else()
  message("Unsupported Platform" FATAL)
endif()

add_executable(makedir main.cpp Directory.h Directory.cpp)
