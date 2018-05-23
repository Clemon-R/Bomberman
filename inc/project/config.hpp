/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** config
*/

#ifndef CONFIG_HPP_
	#define CONFIG_HPP_

	#define	PATH_IMG	"./ressources/images"
	
	#include <iostream>

class	config
{
public:
	std::string	SCALE = "1";
	std::string	FULL_SCREEN = "0";

	std::size_t	WINDOW_WIDTH = 880;
	std::size_t	WINDOW_HEIGHT = 480;
	std::size_t	GAME_SCALE = 1;

	std::size_t	TILE_SIZE = 0;
	std::size_t	TILE_COUNT = 0;
	std::size_t	GAME_AREA = 0;

	void	refresh_config();
};
#endif /* !CONFIG_HPP_ */
