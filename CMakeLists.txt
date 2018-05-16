cmake_minimum_required(VERSION 3.0)

project(bomberman)

set(CMAKE_TYPE_BUILD Debug)
set(CMAKE_CXX_FLAGS, "{CMAKE_CXX_FLAGS} -Iinc -std=c++14")

set(EXECUTABLE_OUTPUT_PATH, "./")

include_directories(./irrlicht-1.8.4/include)

if (UNIX)
  set(IRRLITCH_BIN, "./irrlitch-1.8.4/bin/Linux/")
endif (UNIX)
if (WIN32)
  set(IRRLITCH_BIN, "./irrlitch-1.8.4/bin/Win32-gcc/")
endif (WIN32)

link_directories(${IRRLITCH_BIN})

add_executable(
  bomberman
  src/main.cpp
  )

install (TARGETS irrlitch RUNTIME DESTINATION bin)
