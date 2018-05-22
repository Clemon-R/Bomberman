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
private:
	irr::IrrlichtDevice	*_graphic;
	gui			&_gui;
};
#endif /* !GUI_HANDLER_HPP_ */