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

bomb::bomb(player *parent, irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_design(nullptr), _parent(parent), _start(utils::get_milliseconds()), _exploded(false)
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
	for (auto &fire : _fires)
		fire->remove();
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

void	bomb::run()
{
	if (!_exploded && utils::get_milliseconds() - _start >= 2000)
		explode();
	else if (_exploded){
		kill();
		if (utils::get_milliseconds() - _start >= 3000){
			_parent->bomb_available();
			delete this;
		}
	}
}

void	bomb::kill()
{

}

void	bomb::explode()
{
	irr::scene::ISceneNode	*current = nullptr;
	irr::core::position2di	pos = utils::convert_vector(_design->getPosition(), *_config);

	std::cout << "bomb: exploding...\n";
	if (_design)
		_design->remove();
	_exploded = true;
	for (int i = 0;i < 4;i += 1){
		current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
		if (!current)
			throw exception("Impossible to add cube");
		current->setMaterialTexture(0, database::load_img("tnt", ".png"));
		pos.X += i % 2 - 2 * (i == 3);
		pos.Y += (i + 1) % 2 - 2 * (i == 2);
		current->setPosition(utils::convert_position(pos, *_config));
		pos.X -= i % 2 - 2 * (i == 3);
		pos.Y -= (i + 1) % 2 - 2 * (i == 2);
		_fires.push_back(current);
	}
	current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
	if (!current)
		throw exception("Impossible to add cube");
	current->setMaterialTexture(0, database::load_img("tnt", ".png"));
	current->setPosition(utils::convert_position(pos, *_config));
	_fires.push_back(current);
	std::cout << "bomb: exploded\n";
}