/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** ia
*/

#ifndef IA_HPP_
	#define IA_HPP_

class	player;
	#include "project/game/player.hpp"
	#include <iostream>

class	ia
{
public:
	ia(player *parent);
	~ia();

	void	run();
private:
	player	*_parent;
};
#endif /* !IA_HPP_ */
