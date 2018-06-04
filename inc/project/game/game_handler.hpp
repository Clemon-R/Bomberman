/*
** EPITECH PROJECT, 2018
** indie studi
** File description:
** game_handler
*/

#ifndef GAME_HANDLER_HPP_
	#define GAME_HANDLER_HPP_

	#include "irrlicht/irrlicht.h"
class	game;
	#include "project/game/game.hpp"
	#include "project/enum_list.hpp"
	#include <list>

class	game_handler : public irr::IEventReceiver
{
public:
	game_handler(irr::IrrlichtDevice *graphic, game &game);
	bool	OnEvent(const irr::SEvent& event) override final;
private:
	bool	window_handler(const irr::SEvent& event);
	bool	key_handler(const irr::SEvent& event);

	bool	move_handler(int key);

	irr::IrrlichtDevice	*_graphic;
	std::list<int>		_last;
	game	&_game;
};
#endif /* !GAME_HANDLER_HPP_ */
