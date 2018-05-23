cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD DEBUG)
set(TYPE_BUILD "${CMAKE_TYPE_BUILD}")
set(EXECUTABLE_OUTPUT_PATH, "./")

set(CMAKE_CXX_FLAGS " -Iinc -std=c++14 -g3")

set(BOMBERMAN_GUI
	src/project/gui/gui.cpp
	src/project/gui/gui_handler.cpp
)

set(BOMBERMAN_GAME
	src/project/game/game.cpp
	src/project/game/player.cpp
)

set(BOMBERMAN_PROJECT
	src/project/project.cpp
	src/project/config.cpp
	src/project/database.cpp
	src/project/utils.cpp
	${BOMBERMAN_GUI}
	${BOMBERMAN_GAME}
)

set(BOMBERMAN_SRC
	${BOMBERMAN_PROJECT}
	src/main.cpp
	src/exception.cpp
	src/saver.cpp
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
install(FILES ressources/images/bg_1.jpg ressources/images/bg_2.jpg ressources/images/bg_3.jpg DESTINATION ressources/images)
install(FILES ressources/images/btn_exit_1.png ressources/images/btn_exit_2.png ressources/images/btn_exit_3.png DESTINATION ressources/images)
install(FILES ressources/images/btn_play_1.png ressources/images/btn_play_2.png ressources/images/btn_play_3.png DESTINATION ressources/images)