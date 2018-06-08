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
	player	*target = _game.get_player(1);
	player	*target2 = _game.get_player(2);

	if (!target && !target2)
		return (true);
	if (!event.KeyInput.PressedDown){
		if (_last.back() == event.KeyInput.Key){
			if (target)
				target->stop();
			if (target2)
				target2->stop();
		}
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
	player	*target1 = _game.get_player(1);
	player	*target2 = _game.get_player(2);

	switch (key){
		case irr::KEY_KEY_S:
		case irr::KEY_KEY_Z:
			if (target1){
				auto	x1 = target1->get_parent()->get_floor(target1->get_position().X, target1->get_position().Y);
				auto	tmp1 = x1;
				do {
					tmp1 = x1;
					x1 = target1->get_parent()->get_floor(target1->get_position().X, std::get<1>(*x1) + (key == irr::KEY_KEY_Z ? 1 : -1));
				} while (std::get<2>(*x1) <= GroundType::FIRE);
				target1->move_to(irr::core::position2di(target1->get_position().X, std::get<1>(*tmp1)));
			}
			break;

		case irr::KEY_KEY_O:
		case irr::KEY_KEY_L:
			if (target2){
				auto	x2 = target2->get_parent()->get_floor(target2->get_position().X, target2->get_position().Y);
				auto	tmp2 = x2;
				do {
					tmp2 = x2;
					x2 = target2->get_parent()->get_floor(target2->get_position().X, std::get<1>(*x2) + (key == irr::KEY_KEY_O ? 1 : -1));
				} while (std::get<2>(*x2) <= GroundType::FIRE);
				target2->move_to(irr::core::position2di(target2->get_position().X, std::get<1>(*tmp2)));
			}
			break;
	
		case irr::KEY_KEY_Q:
		case irr::KEY_KEY_D:
			if (target1){
				auto	x1 = target1->get_parent()->get_floor(target1->get_position().X, target1->get_position().Y);
				auto	tmp1 = x1;
				do {
					tmp1 = x1;
					x1 = target1->get_parent()->get_floor(std::get<0>(*x1) + (key == irr::KEY_KEY_Q ? 1 : -1), std::get<1>(*x1));
				} while (std::get<2>(*x1) <= GroundType::FIRE);
				target1->move_to(irr::core::position2di(std::get<0>(*tmp1), target1->get_position().Y));
			}
			break;

		case irr::KEY_KEY_K:
		case irr::KEY_KEY_M:
			if (target2){
				auto	x2 = target2->get_parent()->get_floor(target2->get_position().X, target2->get_position().Y);
				auto	tmp2 = x2;
				do {
					tmp2 = x2;
					x2 = target2->get_parent()->get_floor(std::get<0>(*x2) + (key == irr::KEY_KEY_K ? 1 : -1), std::get<1>(*x2));
				} while (std::get<2>(*x2) <= GroundType::FIRE);
				target2->move_to(irr::core::position2di(std::get<0>(*tmp2), target2->get_position().Y));
			}
			break;

		case irr::KEY_KEY_E:
			if (target1)
				target1->drop_bomb();
			break;

		case irr::KEY_KEY_P:
			if (target2)
				target2->drop_bomb();
			break;

		default:
			return (false);
	}
	std::cout << "game_handler: new key event\n";
	return (true);
}