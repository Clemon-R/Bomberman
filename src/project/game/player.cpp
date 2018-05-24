/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#include "project/game/player.hpp"
#include "exception.hpp"
#include "project/database.hpp"

player::player(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_anim(irr::scene::EMAT_STAND), _rotate(0, 0, 0), _break(false)
{
	std::size_t	mid = _config->GAME_AREA / 2;
	irr::scene::IAnimatedMesh	*mesh = nullptr;

	_driver = _graphic->getVideoDriver();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_smgr)
		throw exception("Impossible to find the driver");
	mesh = _smgr->getMesh("ressources/skin/sydney.md2");
	if (!mesh)
		throw exception("Impossible to load mesh");
	_design = _smgr->addAnimatedMeshSceneNode(mesh);
	if (!_design)
		throw exception("Impossible to create player");
	_design->setMaterialTexture(0, _driver->getTexture("ressources/skin/sydney.bmp"));
	_design->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_design->setMD2Animation(_anim);
	_design->setRotation(_rotate);
	_target = irr::core::vector3df(mid, _config->TILE_SIZE, mid);
	_design->setPosition(_target);	
}

void	player::refresh()
{
	if (_break){
		play();
		_break = false;
	}
	if (_design->getPosition().X == _target.X && _design->getPosition().Z == _target.Z){
		_anim = irr::scene::EMAT_STAND;
		_design->setMD2Animation(_anim);
		_design->setRotation(_rotate);
	}
}

void	player::move_to(const irr::core::position2di &pos)
{
	int	delay = 0;
	irr::core::position2di	old = convert_pos(_target);
	irr::core::position2di	player = get_position();
	irr::scene::ISceneNodeAnimator	*anim = nullptr;

	if ((pos.X == old.X && pos.Y == old.Y) ||
		(player.X == pos.X && player.Y == pos.Y))
		return;
	if (player.X != pos.X){
		delay = (player.X - pos.X) * 100;
		_rotate = irr::core::vector3df(0, delay < 0 ? -90 : 90, 0);
	}
	else if (player.Y != pos.Y){
		delay = (player.Y - pos.Y) * 100;
		_rotate = irr::core::vector3df(0, delay < 0 ? 0 : 180, 0);
	}
	_target = irr::core::vector3df(static_cast<float>(pos.Y) * _config->TILE_SIZE, _design->getPosition().Y, static_cast<float>(pos.X) * _config->TILE_SIZE);
	anim = _smgr->createFlyStraightAnimator(_design->getPosition(), _target, delay < 0 ? delay * -1 : delay);
	if (anim){
		_design->addAnimator(anim);
		anim->drop();
		_anim = irr::scene::EMAT_RUN;
		_design->setMD2Animation(_anim);
		_design->setRotation(_rotate);
	}
}

void	player::play()
{
	if (_design->getPosition().X != _target.X || _design->getPosition().Z != _target.Z)
		move_to(convert_pos(_target));
}

irr::core::position2di	player::convert_pos(const irr::core::vector3df &pos) const
{
	return (irr::core::position2di(pos.Z / _config->TILE_SIZE,
		pos.X / _config->TILE_SIZE));
}

void	player::stop()
{
	_design->removeAnimators();
	_design->setMD2Animation(irr::scene::EMAT_STAND);
	_target = _design->getPosition();
}

void	player::pause()
{
	_break = true;
	_design->removeAnimators();
	_design->setMD2Animation(irr::scene::EMAT_STAND);
}

irr::core::position2di	player::get_position() const
{
	return (convert_pos(_design->getPosition()));
}

irr::core::position2di	player::get_real_position() const
{
	return (irr::core::position2di(_design->getPosition().Z,
		_design->getPosition().X));
}