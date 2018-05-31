/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** bomb
*/

#ifndef BOMB_HPP_
	#define BOMB_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"
class	player;
	#include "project/game/player.hpp"
class	game;
	#include "project/game/game.hpp"
	#include <iostream>
	#include <list>

class	bomb
{
public:
	bomb(game *game_parent, player *parent, irr::IrrlichtDevice *graphic, config *config);
	~bomb();

	void	spawn();
	void	run();
private:
	void	explode();
	void	kill();
	void	remove_brick();

	irr::scene::ISceneNode	*_design;
	game			*_game_parent;
	player			*_parent;
	std::size_t		_start;
	bool			_exploded;
	std::list<irr::scene::ISceneNode *>	_fires;

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;

	config	*_config;
};
#endif /* !BOMB_HPP_ */