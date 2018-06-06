/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game_handler
*/

#include "project/game/game_handler.hpp"
#include <algorithm>

game_handler::game_handler(irr::IrrlichtDevice *graphic, game &game) : _graphic(graphic), _game(game)
{
	std::cout << "game_handler: new instant\n";
}

bool	game_handler::OnEvent(const irr::SEvent& event)
{
	irr::s32	caller = -1;

	if (event.EventType == irr::EET_GUI_EVENT &&
		event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		return (window_handler(event));
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
		!_game.is_break())
		return (key_handler(event));
	return (false);
}

bool	game_handler::window_handler(const irr::SEvent& event)
{
	irr::s32	caller = event.GUIEvent.Caller->getID();

	std::cout << "game_handler: new action\n";
	_game.get_project().get_sound()->play2D("ressources/sounds/btn.mp3");
	switch (caller){
		case CodeEventGame::BREAK:
			_game.pause();
			break;

		case CodeEventGame::CONTINU:
			_game.play();
			break;

		case CodeEventGame::LEAVE:
			_game.back_to_main();
			break;
		
		case CodeEventGame::SAVE:
			_game.save_menu();
			break;
		
		case CodeEventGame::BACKGAME:
			_game.break_menu();
			break;

		case CodeEventGame::SAVEGAME:
			_game.save_game(_game.get_text());
			_game.break_menu();
			break;

		default:
		return (false);
	}
	return (true);
}

bool	game_handler::key_handler(const irr::SEvent& event)
{
	player	*target = _game.get_current();

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

bool	game_handler::move_handler(int key)
{
	player	*target = _game.get_current();
	irr::scene::ISceneNode *test;
	auto	x = target->get_parent()->get_floor(target->get_position().X, target->get_position().Y);
	auto	tmp = x;

	std::cout << "game_handler: new key event\n";
	switch (key){
		case irr::KEY_DOWN:
		case irr::KEY_UP:
		do {
			tmp = x;
			x = target->get_parent()->get_floor(target->get_position().X, std::get<1>(*x) + (key == irr::KEY_UP ? 1 : -1));
		} while (std::get<2>(*x) <= GroundType::FIRE);
		target->move_to(irr::core::position2di(target->get_position().X, std::get<1>(*tmp)));
		break;

		case irr::KEY_LEFT:
		case irr::KEY_RIGHT:
		do {
			tmp = x;
			x = target->get_parent()->get_floor(std::get<0>(*x) + (key == irr::KEY_LEFT ? 1 : -1), std::get<1>(*x));
		} while (std::get<2>(*x) <= GroundType::FIRE);
		target->move_to(irr::core::position2di(std::get<0>(*tmp), target->get_position().Y));
		break;
		
		case irr::KEY_SPACE:
		target->drop_bomb();
		break;

		default:
		return (false);
	}
	return (true);
}