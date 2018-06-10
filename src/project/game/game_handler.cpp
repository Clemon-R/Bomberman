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
	player	*target = _game.get_current(1);
	player	*target2 = _game.get_current(2);

	if (!target && !target2)
		return (true);
	if (!event.KeyInput.PressedDown){
		if (_last.size() > 0 && target){
			if (_last.back() == event.KeyInput.Key)
				target->stop();
			_last.remove(event.KeyInput.Key);
			if (_last.size() > 0)
				move_handler(_last.back());
		}
		if (_last2.size() > 0){
			if (target2 && _last2.back() == event.KeyInput.Key)
				target2->stop();
			_last2.remove(event.KeyInput.Key);
			if (_last2.size() > 0)
				move_handler(_last2.back());
		}
		return (true);
	}
	if (!move_handler(event.KeyInput.Key))
		return (false);
	return (true);
}

bool	game_handler::move_handler(int key)
{
	TYPE_FLOOR	*current = nullptr;
	TYPE_FLOOR	*tmp = nullptr;
	player	*target1 = _game.get_current(1);
	player	*target2 = _game.get_current(2);
	player	*target = nullptr;
	std::list<int>	*last = nullptr;

	switch (key){
		case irr::KEY_KEY_O:
		case irr::KEY_KEY_L:
		case irr::KEY_KEY_S:
		case irr::KEY_KEY_Z:
			target = key == irr::KEY_KEY_S || key == irr::KEY_KEY_Z ? target1 : target2;
			last = key == irr::KEY_KEY_S || key == irr::KEY_KEY_Z ? &_last : &_last2;
			if (!target)
				break;
			current = target->get_parent()->get_floor(target->get_position().X, target->get_position().Y);
			do {
				tmp = current;
				current = target->get_parent()->get_floor(std::get<0>(*tmp), std::get<1>(*tmp) + (key == irr::KEY_KEY_Z || key == irr::KEY_KEY_O ? 1 : -1));
			} while (std::get<2>(*current) <= GroundType::FIRE);
			target->move_to(irr::core::position2di(std::get<0>(*tmp), std::get<1>(*tmp)));
			break;
	
		case irr::KEY_KEY_K:
		case irr::KEY_KEY_M:
		case irr::KEY_KEY_Q:
		case irr::KEY_KEY_D:
			target = key == irr::KEY_KEY_Q || key == irr::KEY_KEY_D ? target1 : target2;
			last = key == irr::KEY_KEY_Q || key == irr::KEY_KEY_D ? &_last : &_last2;
			if (!target)
				break;
			current = target->get_parent()->get_floor(target->get_position().X, target->get_position().Y);
			do {
				tmp = current;
				current = target->get_parent()->get_floor(std::get<0>(*tmp) + (key == irr::KEY_KEY_Q || key == irr::KEY_KEY_K ? 1 : -1), std::get<1>(*tmp));
			} while (std::get<2>(*current) <= GroundType::FIRE);
			target->move_to(irr::core::position2di(std::get<0>(*tmp), std::get<1>(*tmp)));
			break;

		case irr::KEY_KEY_E:
			last = &_last;
			if (target1)
				target1->drop_bomb();
			break;

		case irr::KEY_KEY_P:
			last = &_last2;
			if (target2)
				target2->drop_bomb();
			break;

		default:
			return (false);
	}
	if (last && std::find(last->begin(), last->end(), key) == last->end())
		last->push_back(key);
	std::cout << "game_handler: new key event\n";
	return (true);
}