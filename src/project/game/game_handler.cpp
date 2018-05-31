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

		default:
		return (false);
	}
	return (true);
}

bool	game_handler::key_handler(const irr::SEvent& event)
{
	player	*target = _game.get_player();

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
	player	*target = _game.get_player();
//	irr::scene::ISceneNode *test;

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
		
		case irr::KEY_SPACE:
		target->drop_bomb();
		// test = _graphic->getSceneManager()->addSphereSceneNode(7.5);
		// test->setPosition(irr::core::vector3df(target->get_real_position().Y, 30, target->get_real_position().X));
		break;

		default:
		return (false);
	}
	return (true);
}