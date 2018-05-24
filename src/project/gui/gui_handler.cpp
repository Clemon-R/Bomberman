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
	for (irr::u32 i=0;i < irr::KEY_KEY_CODES_COUNT; ++i)
        	KeyIsDown[i] = false;
}

bool	gui_handler::OnEvent(const irr::SEvent& event)
{
	irr::s32	caller = -1;

	if (event.EventType == irr::EET_GUI_EVENT &&
		event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		return (window_handler(event));
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
		_gui.get_game() &&
		!_gui.get_game()->is_break())
		return (key_handler(event));
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

bool	gui_handler::key_handler(const irr::SEvent& event)
{
	player	*target = _gui.get_game()->get_player();

	if (!target)
		return (true);
	if (!event.KeyInput.PressedDown){
		KeyIsDown[event.KeyInput.Key] = false;
		target->stop();
		return (true);
	}
	if (KeyIsDown[event.KeyInput.Key])
		return (true);
	switch (event.KeyInput.Key){
		case irr::KEY_UP:
		target->move_to(irr::core::position2di(target->get_position().X, 28));
		break;

		case irr::KEY_DOWN:
		target->move_to(irr::core::position2di(target->get_position().X, 1));
		break;

		case irr::KEY_LEFT:
		target->move_to(irr::core::position2di(28, target->get_position().Y));
		break;

		case irr::KEY_RIGHT:
		target->move_to(irr::core::position2di(1, target->get_position().Y));
		break;
	}
	KeyIsDown[event.KeyInput.Key] = true;
	return (true);
}