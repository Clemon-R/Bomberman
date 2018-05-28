/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui_handler
*/

#include "project/gui/gui_handler.hpp"
#include <iostream>
#include <algorithm>

gui_handler::gui_handler(irr::IrrlichtDevice *graphic, gui &gui) : _graphic(graphic), _gui(gui)
{
	std::cout << "gui_handler: new instant\n";
}

bool	gui_handler::OnEvent(const irr::SEvent& event)
{
	irr::s32	caller = -1;

	if (event.EventType == irr::EET_GUI_EVENT &&
		event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		return (window_handler(event));
	return (false);
}

bool	gui_handler::window_handler(const irr::SEvent& event)
{
	irr::s32	caller = event.GUIEvent.Caller->getID();

	switch (caller){
		case CodeEventGui::EXIT:
			_graphic->closeDevice();
			break;

		case CodeEventGui::PLAY:
			_gui.play_game();
			break;

		default:
		return (false);
	}
	return (true);
}