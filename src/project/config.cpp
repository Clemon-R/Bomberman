/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** config
*/

#include "project/config.hpp"

void	config::refresh_config()
{
	GAME_SCALE = std::atoi(SCALE.c_str());

	switch (GAME_SCALE){
		default:
		case 1:
		WINDOW_WIDTH = 880;
		WINDOW_HEIGHT = 480;
		break;

		case 2:
		WINDOW_WIDTH = 1320;
		WINDOW_HEIGHT = 720;
		break;

		case 3:
		WINDOW_WIDTH = 1920;
		WINDOW_HEIGHT = 1080;
		break;
	}
}