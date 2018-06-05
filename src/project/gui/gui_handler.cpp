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

	std::cout << "gui_handler: new action\n";
	_gui.get_project().get_sound()->play2D("ressources/sounds/btn.mp3");
	switch (caller){
		case CodeEventGui::EXIT:
			_graphic->closeDevice();
			break;

		case CodeEventGui::LOAD:
			_gui.load_menu();
			break;

		case CodeEventGui::PLAY:
			_gui.play_game();
			break;

		case CodeEventGui::CHARGE:
			_gui.load_game(_gui.get_text());
			break;

		case CodeEventGui::BACK:
			_gui.main_menu();
			break;

		case CodeEventGui::MULTIPLAYER:
			_gui.multiplayer_menu();
			break;

		default:
		return (false);
	}
	return (true);
}