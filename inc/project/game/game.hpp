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
	#include <list>
	#include <tuple>

enum	GroundType
{
	WALL,
	GROUND,
	BRICK
};

class	game
{
public:
	game(irr::IrrlichtDevice *graphic, config *config);
	~game();

	void	run();
	void	generateFloor();
	void	spawnAll();
private:
	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	std::list<std::tuple<GroundType, irr::video::ITexture *>>	_floor;
	config			*_config;

	std::size_t		_width;
	std::size_t		_height;
};
#endif /* !GAME_HPP_ */
