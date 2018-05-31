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
_design(nullptr), _parent(parent)
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