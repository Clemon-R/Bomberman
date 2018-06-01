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
	#include "project/enum_list.hpp"
	#include <iostream>
	#include <tuple>
	#include <list>

class	bomb
{
public:
	bomb(player *parent, irr::IrrlichtDevice *graphic, config *config);
	~bomb();

	void	spawn();
	void	run();
private:
	void	explode();
	void	change_to_fire(std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *> *floor);
	void	kill();

	std::list<std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *> *>	_fires;

	irr::scene::ISceneNode	*_design;
	player			*_parent;
	std::size_t		_start;
	bool			_exploded;

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;

	config	*_config;
};
#endif /* !BOMB_HPP_ */
