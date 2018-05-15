cmake_minimum_required(VERSION 3.0)

set(CMAKE_TYPE_BUILD Debug)
set(CMAKE_CXX_FLAGS, "{CMAKE_CXX_FLAGS} -Iinc -std=c++14")

add_executable(
  bomberman
  src/main.cpp
)
