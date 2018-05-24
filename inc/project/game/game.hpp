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
	#include "project/game/player.hpp"
class	game_handler;
	#include <iostream>
	#include <list>
	#include <tuple>
	#include <memory>

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

	player	*get_player();

	void	run();
	void	generateFloor();
	void	spawnAll();
	void	pause();

	bool	is_break() const;
private:
	void	play();
	void	drawWall();
	void	setCamera();

	player	*_player;

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;
	std::list<std::tuple<GroundType, irr::video::ITexture *>>	_floor;
	config			*_config;
	bool			_break;
};
#endif /* !GAME_HPP_ */
