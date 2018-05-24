/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui_handler
*/

#ifndef GUI_HANDLER_HPP_
	#define GUI_HANDLER_HPP_

	#include "irrlicht/irrlicht.h"
class	gui;
	#include "project/gui/gui.hpp"
	#include <list>

enum	CodeEventGui
{
	EXIT = 101,
	PLAY,
	PAUSE,
	BACK
};

class	gui_handler : public irr::IEventReceiver
{
public:
	gui_handler(irr::IrrlichtDevice *graphic, gui &gui);
	bool	OnEvent(const irr::SEvent& event) override final;

	bool	key_handler(const irr::SEvent& event);
	bool	window_handler(const irr::SEvent& event);
private:
	bool	move_handler(int key);

	irr::IrrlichtDevice	*_graphic;
	gui			&_gui;
	std::list<int>		_last;
};
#endif /* !GUI_HANDLER_HPP_ */
