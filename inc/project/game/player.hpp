/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

	#include "project/game/bomb.hpp"
	#include "irrlicht/irrlicht.h"
	#include "irrlicht/irrTypes.h"
	#include "irrlicht/ITimer.h"
	#include "project/config.hpp"
class	bomb;
	#include "project/game/bomb.hpp"
class	game;
	#include "project/game/game.hpp"
	#include <iostream>
	#include <vector>
	#include <memory>

class	player
{
public:
	player(std::size_t id, game *parent, irr::IrrlichtDevice *graphic, config *config);
	~player();

	void	refresh();
	void	pause();
	void	stop();

	void	move_to(const irr::core::position2di &pos);

	irr::core::position2di	get_position() const;
	void	set_position(const irr::core::position2di &pos);
	irr::core::position2di	get_real_position() const;
	game	*get_parent() const;
	void	set_rotation(const std::size_t dir);
	const std::size_t	get_id() const;

	void	save_player(std::ofstream &file);
	void	load_player(const std::string &param, const std::string &arg);

	void	spawn();
	void	dead();

	void	drop_bomb();
	void	bomb_available();

	void	set_camera();
	bool	is_alive() const;
private:
	void	play();

	std::size_t	_id;
	bomb		*_bomb;
	bool		_break;
	bool		_alive;

	irr::core::vector3df			_target;
	irr::core::vector3df			_last;

	config					*_config;
	game					*_parent;
	irr::IrrlichtDevice			*_graphic;
	irr::video::IVideoDriver		*_driver;
	irr::scene::ISceneManager		*_smgr;

	irr::scene::IAnimatedMeshSceneNode	*_design;
	irr::core::vector3df			_rotate;
	irr::scene::EMD2_ANIMATION_TYPE		_anim;
	irr::scene::ICameraSceneNode		*_camera;
};
#endif /* !PLAYER_HPP_ */
