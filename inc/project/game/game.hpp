/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#ifndef GAME_HPP_
	#define GAME_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"
	#include <iostream>

class	game
{
public:
	game(irr::IrrlichtDevice *graphic, config *config);
	~game();

	void	run();
	void	spawnAll();
private:
	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	config			*_config;
};
#endif /* !GAME_HPP_ */
