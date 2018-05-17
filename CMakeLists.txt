cmake_minimum_required(VERSION 2.6)

project(bomberman)

set(CMAKE_TYPE_BUILD Debug)
set(EXECUTABLE_OUTPUT_PATH, "./")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-L${CMAKE_SOURCE_DIR}/libs/linux/ -lIrrlicht -Iinc")
endif (CMAKE_COMPILER_IS_GNUCXX)

configure_file(
	${CMAKE_SOURCE_DIR}/inc/main.hpp.in
	${CMAKE_SOURCE_DIR}/inc/main.hpp
)

add_executable(
	bomberman
	${CMAKE_SOURCE_DIR}/src/main.cpp
)
#if (UNIX)
	target_link_libraries(bomberman ${CMAKE_SOURCE_DIR}/libs/linux/libIrrlicht.so)
	install(TARGETS bomberman DESTINATION ${CMAKE_SOURCE_DIR}/bin/linux)
#endif (UNIX)