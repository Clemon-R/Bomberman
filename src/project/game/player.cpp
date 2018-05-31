/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#include "project/game/player.hpp"
#include "exception.hpp"
#include "project/database.hpp"
#include "project/utils.hpp"
#include <fstream>

player::player(irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_anim(irr::scene::EMAT_STAND), _rotate(0, 0, 0), _break(false), _design(nullptr), _bomb(nullptr)
{
	std::size_t	mid = _config->GAME_AREA / 2;

	std::cout << "player: init...\n";
	_driver = _graphic->getVideoDriver();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_smgr)
		throw exception("Impossible to find the driver");
	_target = irr::core::vector3df(mid, _config->TILE_SIZE, mid);
	std::cout << "player: initiated\n";
}

player::~player()
{
	std::cout << "player: destroying...\n";
	std::cout << "player: destoyed\n";
}

void	player::spawn()
{
	irr::scene::IAnimatedMesh	*mesh = nullptr;
	float	size = 0.5f * _config->GAME_SCALE;

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
	_design->setPosition(_target);
	_design->setScale(irr::core::vector3df(size, size, size));
}

void	player::refresh()
{
	if (_break){
		play();
		_break = false;
	}
	if (_anim == irr::scene::EMAT_RUN && _design->getPosition().X == _target.X && _design->getPosition().Z == _target.Z){
		_anim = irr::scene::EMAT_STAND;
		_design->setMD2Animation(_anim);
		_design->setRotation(_rotate);
		std::cout << "player: arrived\n";
	}
	if (_bomb)
		_bomb->run();
}

void	player::bomb_available()
{
	_bomb = nullptr;
}

void	player::move_to(const irr::core::position2di &pos)
{
	int	delay = 0;
	irr::core::position2di	old = utils::convert_vector(_target, *_config);
	irr::core::position2di	player = get_position();
	irr::scene::ISceneNodeAnimator	*anim = nullptr;

	std::cout << "player: moving...\n";
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
		std::cout << "player: start running...\n";
	}
}

void	player::play()
{
	if (_design->getPosition().X != _target.X || _design->getPosition().Z != _target.Z)
		move_to(utils::convert_vector(_target, *_config));
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
	return (utils::convert_vector(_design->getPosition(), *_config));
}

irr::core::position2di	player::get_real_position() const
{
	return (irr::core::position2di(_design->getPosition().Z,
		_design->getPosition().X));
}

void	player::save_player(std::ofstream &file)
{
	irr::core::position2di	pos = get_position();

	std::cout << "player: saving...\n";
	file << "P1_POS=";
	file << pos.X << "," << pos.Y << std::endl;
	std::cout << "player: saved\n";
}

void	player::load_player(const std::string &param, const std::string &arg)
{
	std::size_t	pos;

	std::cout << "player: new param\n";
	if (param.at(0) != 'P' || param.at(2) != '_')
		return;
	if (param.substr(3).compare("POS") == 0){
		if ((pos = arg.find(',')) == std::string::npos)
			return;
		set_position(irr::core::position2di(std::atoi(arg.substr(0, pos).c_str()), std::atoi(arg.substr(pos + 1).c_str())));
	}
}

void	player::set_position(const irr::core::position2di &pos)
{
	_target = utils::convert_position(pos, *_config);
	if (_design)
		_design->setPosition(_target);
}

void	player::set_rotation(const std::size_t dir)
{
	_rotate = irr::core::vector3df(0, dir, 0);
	if (_design)
		_design->setRotation(_rotate);
}

void	player::drop_bomb()
{
	if (!_bomb)
		_bomb = new bomb(this, _graphic, _config);
}