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
	#include <iostream>

class	player
{
public:
	player(irr::IrrlichtDevice *graphic, config *config);

	void	refresh();
	void	pause();

	void	move_to(const irr::core::position2di &pos);
	void	stop();

	irr::core::position2di	get_position() const;
	irr::core::position2di	get_real_position() const;

	void	save_player(std::ofstream &file);
	void	load_player(const std::string &param, const std::string &arg);
private:
	void	play();
	irr::core::position2di	convert_pos(const irr::core::vector3df &pos) const;

	irr::core::vector3df	_rotate;
	irr::scene::EMD2_ANIMATION_TYPE	_anim;

	bool	_break;
	irr::core::vector3df			_target;
	config					*_config;
	irr::IrrlichtDevice			*_graphic;
	irr::video::IVideoDriver		*_driver;
	irr::scene::ISceneManager		*_smgr;

	irr::scene::IAnimatedMeshSceneNode	*_design;
};
#endif /* !PLAYER_HPP_ */
