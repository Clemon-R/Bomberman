/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

	#include "irrlicht/irrlicht.h"
	#include "irrklang/irrKlang.h"
	#include "project/config.hpp"
class	bomb;
	#include "project/game/bomb.hpp"
class	game;
	#include "project/game/game.hpp"
class	ia;
	#include "project/game/ia.hpp"
	#include <iostream>
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
	void	stop_sound();

	void	save_player(std::ofstream &file);
	void	load_player(const std::string &param, const std::string &arg);

	void	spawn();
	void	dead();

	void	drop_bomb();
	void	bomb_available();

	void	set_camera();
	bool	is_alive() const;
	ia	*get_ia();
	void	set_ia();
	bool	is_moving() const;
	irr::core::position2di	get_position() const;
	void	set_position(const irr::core::position2di &pos);
	irr::core::position2di	get_real_position() const;
	game	*get_parent() const;
	void	set_rotation(const std::size_t dir);
	const std::size_t	get_id() const;
private:
	void	play();

	float	get_volume();

	std::size_t	_id;
	bomb		*_bomb;
	bool		_break;
	bool		_alive;
	bool		_moving;
	std::unique_ptr<ia>	_ia;

	irr::core::vector3df			_target;
	irr::core::vector3df			_last;

	config					*_config;
	irr::IrrlichtDevice			*_graphic;
	irrklang::ISound			*_sound;
	irr::video::IVideoDriver		*_driver;
	irr::scene::ISceneManager		*_smgr;

	irr::scene::IAnimatedMeshSceneNode	*_design;
	irr::core::vector3df			_rotate;
	irr::scene::EMD2_ANIMATION_TYPE		_anim;
	irr::scene::ICameraSceneNode		*_camera;

	game					*_parent;
};
#endif /* !PLAYER_HPP_ */
