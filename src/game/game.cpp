/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#include "game/game.hpp"

game::game() : _graphic(nullptr)
{
	std::cout << "game: init...\n";
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destructing...\n";
	std::cout << "game: destructed\n";
}

void	game::init_of_graphic()
{
	std::cout << "game: init of the graphic...\n";
	_graphic.reset(
		irr::createDevice(
			irr::video::EDT_SOFTWARE,
			irr::core::dimension2d<irr::u32>(640, 480),
			16,
			FULL_SCREEN,
			false,
			VERTICAL_SYNC,
			nullptr
		)
	);
	if (!_graphic)
		throw exception("Impossible to create the graphic");
	_graphic->setWindowCaption(L"The bomberman - by Epitech students");
	std::cout << "game: graphic initiated\n";
}

void	game::run()
{
	irr::video::IVideoDriver	*driver = nullptr;

	if (!_graphic)
		throw exception("Impossible to run the game, don't have graphic");
	driver = _graphic->getVideoDriver();
	if (!driver)
		throw exception("Impossible to get the video driver");
	std::cout << "game: running...\n";
	while (_graphic->run()){
		driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
		driver->endScene();
	}
	std::cout << "game: end running\n";
}