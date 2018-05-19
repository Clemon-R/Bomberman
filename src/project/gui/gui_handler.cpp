/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui_handler
*/

#include "project/gui/gui_handler.hpp"
#include <iostream>

gui_handler::gui_handler(irr::IrrlichtDevice *graphic) : _graphic(graphic)
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

		default:
		return (false);
	}
	return (true);
}