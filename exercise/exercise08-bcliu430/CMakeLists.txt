# cmake_minimun_required(VERSION 3.5)
cmake_minimum_required(VERSION 3.5)

project(exercise CXX)

set(treap_src 
  treap_bst.h treap_bst.txx
  compress.cpp)

set(test_src
  catch.hpp
  treap_bst.h
  treap_bst.txx
  test_treap.cpp)

add_executable(compress ${treap_src})

add_executable(unitTest ${test_src} ${treap_src})
enable_testing()
add_test(unitTest unitTest)

