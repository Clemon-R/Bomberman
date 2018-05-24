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
_break(false), _player(nullptr)
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_env || !_smgr)
		throw exception("Impossible to find the driver");
	generateFloor();
	_player = new player(_graphic, _config);
	//_player->move_to(irr::core::position2di(_player->get_position().X, _player->get_position().Y + 13));
	_player->refresh();
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destroying\n";
	std::cout << "game: destroyed\n";
}

void	game::run()
{
	if (_break){
		play();
		_break = false;
	}
	if (_player)
		_player->refresh();
}

void	game::play()
{
}

void	game::generateFloor()
{
	irr::video::ITexture	*ground = database::load_img("ground");
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	std::size_t	offset = 0;

	if (!ground || !wall)
		throw exception("Impossible to load image");
	_config->TILE_SIZE = ground->getSize().Height;
	_config->TILE_COUNT = _config->WINDOW_HEIGHT / _config->TILE_SIZE;
	_config->GAME_AREA = _config->TILE_COUNT * _config->TILE_SIZE;
	for (int i = 0;i < _config->TILE_COUNT * _config->TILE_COUNT;i += 1){
		if (i % _config->TILE_COUNT == 0 || i / _config->TILE_COUNT == 0
		|| i % _config->TILE_COUNT == _config->TILE_COUNT - 1 || i / _config->TILE_COUNT == _config->TILE_COUNT - 1)
			_floor.push_back(std::make_tuple(GroundType::WALL, wall));
		else
			_floor.push_back(std::make_tuple(GroundType::GROUND, ground));
	}
	drawWall();
	setCamera();
}

void	game::setCamera()
{
	irr::scene::ICameraSceneNode	*cam = _smgr->addCameraSceneNode();
	std::size_t			mid = _config->GAME_AREA / 2;

	cam->setPosition(irr::core::vector3df(mid - _config->TILE_SIZE / 2, _config->GAME_AREA * 0.74, mid));
	cam->setTarget(irr::core::vector3df(mid - _config->TILE_SIZE / 2, 0, mid));
}

void	game::drawWall()
{
	std::list<std::tuple<GroundType, irr::video::ITexture *>>::iterator	it = _floor.begin();
	irr::scene::IMeshSceneNode *current = nullptr;

	for (int i = 0;it != _floor.end() && i < _config->TILE_COUNT * _config->TILE_COUNT;i += 1){
		current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
		if (!current)
			continue;
		current->setPosition(irr::core::vector3df(
			(i / _config->TILE_COUNT) * _config->TILE_SIZE,
			std::get<0>(*it) != GroundType::GROUND ? _config->TILE_SIZE : 0,
			(i % _config->TILE_COUNT) * _config->TILE_SIZE
		));
		current->setMaterialTexture(0, std::get<1>(*it));
		it++;
	}
}

void	game::spawnAll()
{
}

void	game::pause()
{
	if (_player)
		_player->pause();
	_break = true;
}

player	*game::get_player()
{
	return (_player);
}

bool	game::is_break() const
{
	return (_break);
}