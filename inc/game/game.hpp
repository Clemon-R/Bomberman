/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#ifndef GAME_HPP_
	#define GAME_HPP_

	#include "irrlicht/irrlicht.h"
	#include "exception.hpp"
	#include <iostream>
	#include <memory>

	#define	FULL_SCREEN	false
	#define	VERTICAL_SYNC	false

class	game
{
public:
	game();
	~game();

	void	init_of_graphic();
	void	run();
private:
	std::unique_ptr<irr::IrrlichtDevice>	_graphic;
};
#endif /* !GAME_HPP_ */
