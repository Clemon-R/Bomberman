/*
** EPITECH PROJECT, 2018
** indie studip
** File description:
** ia
*/

#include "project/game/ia.hpp"

ia::ia(player *parent) : _parent(parent)
{
	std::cout << "ia: init...\n";
	std::cout << "ia: initiated\n";
}

ia::~ia()
{
	std::cout << "ia: destructing...\n";
	std::cout << "ia: destructed\n";
}

void	ia::run()
{
	
}