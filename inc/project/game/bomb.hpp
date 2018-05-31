/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** bomb class declaration
*/

#ifndef BOMB_HPP_
	#define BOMB_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"
	#include <iostream>

class	bomb
{
public:
	bomb(irr::core::vector3df);
	~bomb();

private:
	void	put_bomb();
	void	explode_bomb();

	
};

#endif