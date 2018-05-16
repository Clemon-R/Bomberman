cmake_minimum_required(VERSION 3.0)

project(bomberman)

set(CMAKE_TYPE_BUILD Debug)

set(EXECUTABLE_OUTPUT_PATH, "./")
set(IRRLITCH, "irrlicht")

if (UNIX)
  set(IRRLITCH_BIN, "./irrlicht-1.8.4/lib/Linux/")
endif (UNIX)
if (WIN32)
  set(IRRLITCH_BIN, "./irrlicht-1.8.4/lib/Win32-gcc/")
endif (WIN32)

set(CMAKE_CXX_FLAGS, "{CMAKE_CXX_FLAGS} -L${IRRLITCH_BIN} -lIrrlicht -Iinc ttt -std=c++14")

add_executable(
  bomberman
  src/main.cpp
  )