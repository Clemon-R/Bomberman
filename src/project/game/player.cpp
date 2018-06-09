/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** player
*/

#include "project/game/player.hpp"
#include "project/game/bomb.hpp"
#include "exception.hpp"
#include "project/database.hpp"
#include "project/utils.hpp"
#include <fstream>
#include <complex>

player::player(std::size_t id, game *parent, irr::IrrlichtDevice *graphic, config *config) : _graphic(graphic), _config(config),
_anim(irr::scene::EMAT_STAND), _rotate(0, 0, 0), _break(false), _design(nullptr), _bomb(nullptr), _parent(parent), _id(id), _alive(true),
_camera(nullptr), _ia(nullptr), _moving(false), _sound(nullptr)
{
	std::size_t	mid = _config->GAME_AREA / 2;

	std::cout << "player: init...\n";
	_driver = _graphic->getVideoDriver();
	_smgr = _graphic->getSceneManager();
	if (!_driver || !_smgr)
		throw exception("Impossible to find the driver");
	_target = irr::core::vector3df(mid, _config->TILE_SIZE, mid);
	_last = _target;
	std::cout << "player: initiated\n";
}

player::~player()
{
	std::cout << "player: destroying...\n";
	std::cout << "player: destoyed\n";
}

void	player::dead()
{
	stop_sound();
	if (_design)
		_design->remove();
	if (_camera)
		_camera->remove();
	_camera = nullptr;
	_design = nullptr;
	_alive = false;
}

void	player::spawn()
{
	irr::scene::IAnimatedMesh	*mesh = nullptr;
	float			size = 0.3f * _config->GAME_SCALE;
	irr::core::vector3df	old = _target;

	if (!_alive)
		return;
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
	_design->setPosition(_last);
	_design->setScale(irr::core::vector3df(size, size, size));
	if (_last.X != _target.X || _last.Z != _target.Z)
		move_to(utils::convert_vector(old, *_config));
}

void	player::refresh()
{
	if (!_design || !_alive)
		return;
	if (_break)
		play();
	_break = false;
	if (_ia)
		_ia->run();
	_last = irr::core::vector3df(_design->getPosition().X + _config->TILE_SIZE / 2, _design->getPosition().Y, _design->getPosition().Z + _config->TILE_SIZE / 2);
	if (_camera){
		_camera->setPosition(irr::core::vector3df(_last.X - _config->TILE_SIZE * 4, _config->TILE_SIZE * 4, _last.Z));
		_camera->setTarget(_last);
	}
	if (_sound)
		_sound->setVolume(get_volume());
	if (_anim == irr::scene::EMAT_RUN && _design->getPosition().X == _target.X && _design->getPosition().Z == _target.Z){
		_anim = irr::scene::EMAT_STAND;
		_design->setMD2Animation(_anim);
		_design->setRotation(_rotate);
		_moving = false;
		stop_sound();
		std::cout << "player: arrived\n";
	}
}

void	player::bomb_available()
{
	if (!_bomb)
		return;
	_bomb = nullptr;
}

void	player::move_to(const irr::core::position2di &pos)
{
	int	delay = 0;
	irr::core::position2di	old = utils::convert_vector(_target, *_config);
	irr::core::position2di	player = get_position();
	irr::scene::ISceneNodeAnimator	*anim = nullptr;

	if (!_design || !_alive)
		return;
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
	if (_moving)
		stop();
	_target = utils::convert_position(pos, *_config);
	anim = _smgr->createFlyStraightAnimator(_design->getPosition(), _target, delay < 0 ? delay * -1 : delay);
	if (anim){
		_design->addAnimator(anim);
		anim->drop();
		_anim = irr::scene::EMAT_RUN;
		_design->setMD2Animation(_anim);
		_design->setRotation(_rotate);
		_moving = true;
		_sound = _parent->get_project().get_sound()->play2D("ressources/sounds/run.mp3", true, false, true);
		_sound->setVolume(get_volume());
		std::cout << "player: start running...\n";
	}
}

void	player::play()
{
	irr::core::vector3df	tmp = _target;

	_target = _last;
	if (tmp.X != _target.X || tmp.Z != _target.Z)
		move_to(utils::convert_vector(tmp, *_config));
}

void	player::stop()
{
	if (!_design)
		return;
	std::cout << "player: stop the movement\n";
	_design->removeAnimators();
	_design->setMD2Animation(irr::scene::EMAT_STAND);
	_target = _design->getPosition();
	stop_sound();
}

void	player::pause()
{
	std::cout << "player: pause\n";
	_break = true;
	if (!_design)
		return;
	_design->removeAnimators();
	_design->setMD2Animation(irr::scene::EMAT_STAND);
}

irr::core::position2di	player::get_position() const
{
	return (utils::convert_vector(_last, *_config));
}

irr::core::position2di	player::get_real_position() const
{
	return (irr::core::position2di(_last.Z,
		_last.X));
}

void	player::save_player(std::ofstream &file)
{
	irr::core::position2di	pos = get_position();

	std::cout << "player: saving...\n";
	file << "P" << _id << "_POS=";
	file << pos.X << "," << pos.Y << std::endl;
	file << "P" << _id << "_ALIVE=" << (_alive ? "1" : "0") << std::endl;
	file << "P" << _id << "_IA=" << (_ia ? "1" : "0") << std::endl;
	std::cout << "player: saved\n";
}

void	player::load_player(const std::string &param, const std::string &arg)
{
	std::size_t	pos;

	std::cout << "player: loading param - " << param << "\n";
	if (param.compare("POS") == 0){
		if ((pos = arg.find(',')) == std::string::npos)
			return;
		set_position(irr::core::position2di(std::atoi(arg.substr(0, pos).c_str()), std::atoi(arg.substr(pos + 1).c_str())));
	} else if (param.compare("ALIVE") == 0 && arg.compare("0") == 0)
		_alive = false;
	else if (param.compare("IA") == 0 && arg.compare("0") == 0)
		_ia.reset(nullptr);
}

void	player::set_position(const irr::core::position2di &pos)
{
	std::cout << "player: new pos\n";
	_target = utils::convert_position(pos, *_config);
	_last = _target;
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
	if (_bomb)
		return;
	std::cout << "player: dropping a bomb\n";
	_bomb = new bomb(this, _graphic, _config);
	_parent->get_bombs().push_back(_bomb);
}

game	*player::get_parent() const
{
	return (_parent);
}

const std::size_t	player::get_id() const
{
	return (_id);
}

void	player::set_camera()
{
	if (_camera)
		return;
	std::cout << "player: adding a camera\n";
	_camera = _smgr->addCameraSceneNode();
	_camera->setPosition(irr::core::vector3df(_last.X - _config->TILE_SIZE * 4, _config->TILE_SIZE * 4, _last.Z));
	_camera->setTarget(_last);
}

bool	player::is_alive() const
{
	return (_alive);
}

void	player::set_ia()
{
	_ia.reset(new ia(this));
}

void	player::remove_ia()
{
	_ia.reset(nullptr);
}

ia	*player::get_ia()
{
	return (_ia.get());
}

bool	player::is_moving() const
{
	return (_moving);
}

void	player::stop_sound()
{
	if (_sound){
		_sound->stop();
		_sound->drop();
		_sound = nullptr;
	}
}

float	player::get_volume()
{
	player	*current = _parent->get_current(1);
	irr::core::position2di	pos = current->get_position();
	irr::core::position2di	own = get_position();
	float		distance = 1.0f;
	double		cell_x = abs(pos.X - own.X);
	double		cell_y = abs(pos.Y - own.Y);
	double		max = (_config->TILE_COUNT - 2) / 2;

	if ((cell_x == 0 && cell_y == 0) || _parent->is_multiplayer())
		return (1);
	else if (cell_x > max || cell_y > max)
		return (0);
	distance -= (cell_x + cell_y) / max;
	std::cout << "player: sound - " << distance << std::endl;
	return (distance);
}