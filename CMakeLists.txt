cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD DEBUG)
set(TYPE_BUILD "${CMAKE_TYPE_BUILD}")
set(EXECUTABLE_OUTPUT_PATH, "./")

set(CMAKE_CXX_FLAGS " -Iinc -std=c++14")

set(BOMBERMAN_GAME
	src/game/game.cpp
)

set(BOMBERMAN_SRC
	${BOMBERMAN_GAME}
	src/main.cpp
	src/exception.cpp
)

add_executable(
	bomberman
	${BOMBERMAN_SRC}
)

if (UNIX)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,.")
	if (TYPE_BUILD STREQUAL "DEBUG")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin/linux")
	endif (TYPE_BUILD STREQUAL "DEBUG")
	if (TYPE_BUILD STREQUAL "RELEASE")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/bin/bomberman")
	endif (TYPE_BUILD STREQUAL "RELEASE")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/libIrrlicht.so.1.8)
	install(FILES libIrrlicht.so.1.8 DESTINATION .)
endif (UNIX)
if (WIN32)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
	if (TYPE_BUILD STREQUAL "DEBUG")
		set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin/win")
	endif (TYPE_BUILD STREQUAL "DEBUG")
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/Irrlicht.dll)
	install(FILES Irrlicht.dll DESTINATION .)
endif (WIN32)

install(TARGETS bomberman DESTINATION .)
install(FILES test/sydney.bmp test/sydney.md2 DESTINATION test)