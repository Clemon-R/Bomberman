/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#include "project/game/player.hpp"
#include "exception.hpp"

player::player(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_anim(irr::scene::EMAT_RUN), _speed(0), _rotate(0, 0, 0)
{
	std::size_t	mid = _config->GAME_AREA / 2;
	irr::scene::IAnimatedMesh	*mesh = nullptr;

	_driver = _graphic->getVideoDriver();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_smgr)
		throw exception("Impossible to find the driver");
	mesh = _smgr->getMesh("test/sydney.md2");
	if (!mesh)
		throw exception("Impossible to load mesh");
	_design = _smgr->addAnimatedMeshSceneNode(mesh);
	if (!_design)
		throw exception("Impossible to create player");
	_design->setMaterialTexture(0, _driver->getTexture("test/sydney.bmp"));
	_design->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_design->setMD2Animation(_anim);
	_design->setRotation(_rotate);
	_design->setAnimationSpeed(_speed);
	_design->setPosition(irr::core::vector3df(mid, _config->TILE_SIZE,mid));
}

void	player::refresh()
{
	std::size_t	mid = _config->GAME_AREA / 2;
	irr::scene::ISceneNodeAnimator* anim = _smgr->createFlyStraightAnimator(_design->getPosition(),
	irr::core::vector3df((_config->TILE_COUNT - 2) * _config->TILE_SIZE, _config->TILE_SIZE,mid), 3000, false);

	if (anim){
		_design->addAnimator(anim);
		anim->drop();
	}
	_design->setAnimationSpeed(_speed);
	_design->setMD2Animation(_anim);
	_design->setRotation(_rotate);
}


void	player::pause()
{
	_design->removeAnimators();
	_design->setAnimationSpeed(0);
	_design->setMD2Animation(irr::scene::EMAT_STAND);
	_design->setRotation(_rotate);
}