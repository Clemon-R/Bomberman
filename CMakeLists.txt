cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD Release)
set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/bomberman")
set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin/mingw32-make.exe")
set(EXECUTABLE_OUTPUT_PATH, "./")

set(CMAKE_CXX_FLAGS " -Iinc")
set(CMAKE_CXX_FLAGS_RELEASE " -Iinc")

configure_file(
	${CMAKE_SOURCE_DIR}/inc/main.hpp.in
	${CMAKE_SOURCE_DIR}/inc/main.hpp
)

add_executable(
	bomberman
	${CMAKE_SOURCE_DIR}/src/main.cpp
)
if (UNIX)
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/libIrrlicht.so)
endif (UNIX)
if (WIN32)
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/Irrlicht.dll)
endif (WIN32)