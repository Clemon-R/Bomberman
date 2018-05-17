cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD Release)
set(EXECUTABLE_OUTPUT_PATH, "./")

set(CMAKE_CXX_FLAGS " -Iinc")
set(CMAKE_CXX_FLAGS_RELEASE " -Iinc")

set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

configure_file(
	${CMAKE_SOURCE_DIR}/inc/main.hpp.in
	${CMAKE_SOURCE_DIR}/inc/main.hpp
)

add_executable(
	bomberman
	${CMAKE_SOURCE_DIR}/src/main.cpp
)
if (UNIX)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${CMAKE_SOURCE_DIR}")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/libIrrlicht.so.1.8)
endif (UNIX)
if (WIN32)
	set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/bomberman")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/Irrlicht.dll)
endif (WIN32)