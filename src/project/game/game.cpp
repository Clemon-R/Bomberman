/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#include "project/game/game.hpp"
#include "project/utils.hpp"
#include "project/database.hpp"
#include "exception.hpp"

game::game(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_width(0), _height(0)
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	if (!_driver || !_env)
		throw exception("Impossible to find the driver");
	generateFloor();
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destroying\n";
	std::cout << "game: destroyed\n";
}

void	game::run()
{

}

void	game::generateFloor()
{
	irr::video::ITexture	*ground = database::load_img("ground");
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	std::size_t	offset = 0;

	if (!ground || !wall)
		throw exception("Impossible to load image");
	_width = _config->WINDOW_HEIGHT / ground->getSize().Height;
	_height = _width;
	for (int i = 0;i < _width * _height;i += 1){
		if (i % _width == 0 || i / _height == 0
		|| i % _width == _width - 1 || i / _height == _height - 1)
			_floor.push_back(std::make_tuple(GroundType::WALL, wall));
		else
			_floor.push_back(std::make_tuple(GroundType::GROUND, ground));
	}
}

void	game::spawnAll()
{
	std::list<std::tuple<GroundType, irr::video::ITexture *>>::iterator	it = _floor.begin();
	irr::video::ITexture	*ground = database::load_img("ground");
	std::size_t	offset = (_config->WINDOW_WIDTH - ground->getSize().Width * _width) / 2;

	for (int i = 0;it != _floor.end() && i < _width * _height;i += 1){
		_driver->draw2DImage(
			std::get<1>(*it),
			irr::core::position2di(offset + std::get<1>(*it)->getSize().Width * (i % _width), i / _height * std::get<1>(*it)->getSize().Height),
			utils::get_center_img(std::get<1>(*it), irr::core::position2di(std::get<1>(*it)->getSize().Width, std::get<1>(*it)->getSize().Height))
		);
		it++;
	}
}