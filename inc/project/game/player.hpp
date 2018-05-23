/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"

class	player
{
public:
	player(irr::IrrlichtDevice *graphic, config *config);

	void	refresh();
	void	pause();
private:
	std::size_t		_speed;
	irr::core::vector3df	_rotate;
	irr::scene::EMD2_ANIMATION_TYPE	_anim;

	config					*_config;
	irr::IrrlichtDevice			*_graphic;
	irr::video::IVideoDriver		*_driver;
	irr::scene::ISceneManager		*_smgr;

	irr::scene::IAnimatedMeshSceneNode	*_design;
};
#endif /* !PLAYER_HPP_ */
