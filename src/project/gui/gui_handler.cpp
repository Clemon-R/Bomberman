/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui_handler
*/

#include "project/gui/gui_handler.hpp"
#include <iostream>

gui_handler::gui_handler(irr::IrrlichtDevice *graphic, gui &gui) : _graphic(graphic), _gui(gui)
{
	std::cout << "gui_handler: new instant\n";
}

bool	gui_handler::OnEvent(const irr::SEvent& event)
{
	irr::s32	caller = -1;

	if (event.EventType != irr::EET_GUI_EVENT
	|| event.GUIEvent.EventType != irr::gui::EGET_BUTTON_CLICKED)
		return (false);
	caller = event.GUIEvent.Caller->getID();
	switch (caller){
		case CodeEventGui::EXIT:
			_graphic->closeDevice();
			break;

		case CodeEventGui::PLAY:
			_gui.set_state(GuiState::GAME);
			break;

		case CodeEventGui::PAUSE:
			_gui.set_state(GuiState::BREAK);
			break;
		
		case CodeEventGui::BACK:
			_gui.set_state(GuiState::MAIN);
			break;

		default:
		return (false);
	}
	return (true);
}