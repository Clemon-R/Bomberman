cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD RELEASE)
set(TYPE_BUILD "${CMAKE_TYPE_BUILD}")
set(EXECUTABLE_OUTPUT_PATH, "./")

set(CMAKE_CXX_FLAGS " -Iinc")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows -Wl,-rpath -Wl,.")

configure_file(
	${CMAKE_SOURCE_DIR}/inc/main.hpp.in
	${CMAKE_SOURCE_DIR}/inc/main.hpp
)

add_executable(
	bomberman
	${CMAKE_SOURCE_DIR}/src/main.cpp
)

if (UNIX)
	if (TYPE_BUILD STREQUAL "DEBUG")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin/linux")
	endif (TYPE_BUILD STREQUAL "DEBUG")
	if (TYPE_BUILD STREQUAL "RELEASE")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/bin/bomberman")
	endif (TYPE_BUILD STREQUAL "RELEASE")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/libIrrlicht.so.1.8)
endif (UNIX)
if (WIN32)
	if (TYPE_BUILD STREQUAL "DEBUG")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin/win")
	endif (TYPE_BUILD STREQUAL "DEBUG")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/Irrlicht.dll)
endif (WIN32)

install(TARGETS bomberman DESTINATION .)
install(FILES libIrrlicht.so.1.8 Irrlicht.dll DESTINATION .)
install(FILES test/sydney.bmp test/sydney.md2 DESTINATION test)