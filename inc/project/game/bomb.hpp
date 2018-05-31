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
	#include <iostream>

class	bomb
{
public:
	bomb(player *parent, irr::IrrlichtDevice *graphic, config *config);
	~bomb();

	void	spawn();
private:
	irr::scene::ISceneNode	*_design;
	player			*_parent;

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;

	config	*_config;
};
#endif /* !BOMB_HPP_ */
