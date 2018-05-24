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
		if (_last.back() == event.KeyInput.Key)
			target->stop();
		_last.remove(event.KeyInput.Key);
		if (_last.size() > 0)
			move_handler(_last.back());
		return (true);
	}
	if (!move_handler(event.KeyInput.Key))
		return (false);
	if (std::find(_last.begin(), _last.end(), event.KeyInput.Key) == _last.end())
		_last.push_back(event.KeyInput.Key);
	return (true);
}

bool	gui_handler::move_handler(int key)
{
	player	*target = _gui.get_game()->get_player();

	switch (key){
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

		default:
		return (false);
	}
	return (true);
}