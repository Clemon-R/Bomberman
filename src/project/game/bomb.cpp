/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** bomb
*/

#include "project/game/bomb.hpp"
#include "exception.hpp"
#include "project/database.hpp"
#include "project/utils.hpp"
#include <algorithm>
#include <string>

bomb::bomb(player *parent, irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_design(nullptr), _parent(parent), _start(utils::get_milliseconds()), _exploded(false), _end(false)
{
	std::cout << "bomb: init...\n";
	if (!_parent)
		throw exception("Bomb need parent");
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
	_smgr = _graphic->getSceneManager();
	if (!_driver || !_env || !_smgr)
		throw exception("Impossible to find the driver");
	spawn();
	std::cout << "bomb: initiated\n";
}

bomb::~bomb()
{
	std::cout << "bomb: destroying...\n";
	for (auto &fire : _fires){
		std::get<4>(*fire)->remove();
		std::get<4>(*fire) = nullptr;
	}
	std::cout << "bomb: destoyed\n";
}

void	bomb::spawn()
{
	_design = _smgr->addCubeSceneNode(_config->TILE_SIZE);
	if (!_design)
		throw exception("Impossible to add cube");
	_design->setMaterialTexture(0, database::load_img("tnt", ".png"));
	_design->setPosition(utils::convert_position(_parent->get_position(), *_config));
}

bool	bomb::run()
{
	if (!_exploded && utils::get_milliseconds() - _start >= 2000)
		explode();
	else if (_exploded){
		kill();
		if (utils::get_milliseconds() - _start >= 3000){
			remove_brick();
			_parent->bomb_available();
			delete this;
			return (false);
		}
	}
	return (true);
}

void	bomb::kill_by_list(std::list<player *> &list)
{
	for (auto &elem : list)
		elem->dead();
}

void	bomb::remove_brick()
{
	std::cout << "A" << std::endl;
	irr::scene::ISceneNode	*current = nullptr;
	std::cout << "B" << std::endl;
	irr::core::position2di	pos = utils::convert_vector(_design->getPosition(), *_config);
	std::cout << "C" << std::endl;
	// std::list<std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>>::reverse_iterator	y = _game_parent->get_floor().rbegin();
	// std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>::iterator	x;

	std::cout << "bomb: removing brick..." << std::endl;
	for (int i = 0; i < 4; i += 1){
		// for (;y != _game_parent->get_floor().rend();y++){
		// 	x = y->begin();
		// 	for (;x != y->end();x++){
		// 		std::cout << "get0:" << std::get<0>(*x) << std::endl;
		// 		std::cout << "get1:" << std::get<1>(*x) << std::endl;
		// 		std::cout << "get2:" << std::get<2>(*x) << std::endl;
		// 	}
		// }
		current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
		if (!current)
			throw exception("Impossible to add cube");
		current->setMaterialTexture(0, database::load_img("ground"));
		pos.X += i % 2 - 2 * (i == 3);
		pos.Y += (i + 1) % 2 - 2 * (i == 2);
		current->setPosition(utils::convert_position(pos, *_config));
		pos.X -= i % 2 - 2 * (i == 3);
		pos.Y -= (i + 1) % 2 - 2 * (i == 2);
	}
	current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
	if (!current)
		throw exception("Impossible to add cube");
	current->setMaterialTexture(0, database::load_img("ground"));
	current->setPosition(utils::convert_position(pos, *_config));
	std::cout << "bomb: brick removed" << std::endl;
}

void	bomb::kill()
{
	irr::core::position2di	pos = utils::convert_vector(_design->getPosition(), *_config);
	std::list<player *>	list;

	for (int i = 0;i < 4;i += 1){
		pos.X += i % 2 - 2 * (i == 3);
		pos.Y += (i + 1) % 2 - 2 * (i == 2);
		list = _parent->get_parent()->get_player_by_pos(pos.X, pos.Y);
		kill_by_list(list);
		pos.X -= i % 2 - 2 * (i == 3);
		pos.Y -= (i + 1) % 2 - 2 * (i == 2);
	}
	list = _parent->get_parent()->get_player_by_pos(pos.X, pos.Y);
	kill_by_list(list);
}

void	bomb::change_to_fire(std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *> *floor)
{
	irr::video::ITexture	*fire = database::load_img("fire", ".png");

	if (!floor || std::get<2>(*floor) == GroundType::WALL)
		return;
	if (!fire)
		throw exception("Impossible to load fire");
	std::get<3>(*floor) = fire;
	std::get<2>(*floor) = GroundType::FIRE;
	if (std::get<4>(*floor))
		std::get<4>(*floor)->setMaterialTexture(0, std::get<3>(*floor));
	else
		_parent->get_parent()->add_wall(*floor);
	_fires.push_back(floor);
}

void	bomb::explode()
{
	irr::core::position2di	pos = utils::convert_vector(_design->getPosition(), *_config);
	std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>	*ground = nullptr;

	std::cout << "bomb: exploding...\n";
	if (_design)
		_design->remove();
	_exploded = true;
	for (int i = 0;i < 4;i += 1){
		pos.X += i % 2 - 2 * (i == 3);
		pos.Y += (i + 1) % 2 - 2 * (i == 2);
		ground = _parent->get_parent()->get_floor(pos.X, pos.Y);
		change_to_fire(ground);
		pos.X -= i % 2 - 2 * (i == 3);
		pos.Y -= (i + 1) % 2 - 2 * (i == 2);
	}
	ground = _parent->get_parent()->get_floor(pos.X, pos.Y);
	change_to_fire(ground);
	_design = std::get<4>(*ground);
	std::cout << "bomb: exploded\n";
}