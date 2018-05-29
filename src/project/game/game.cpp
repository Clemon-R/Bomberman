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
#include "project/gui/gui.hpp"

game::game(irr::IrrlichtDevice *graphic, config *config, project *project) : _graphic(graphic), _config(config),
_break(false), _player(nullptr), _project(project), _handler(new game_handler(graphic, *this))
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_env || !_smgr)
		throw exception("Impossible to find the driver");
	generate_floor();
	_player = new player(_graphic, _config);
	_player->refresh();
	game_menu();
	_graphic->setEventReceiver(_handler.get());
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destroying\n";
	std::cout << "game: destroyed\n";
}

void	game::break_menu()
{
	irr::video::ITexture	*bg = database::load_img("break", ".png");
	irr::video::ITexture	*img = database::load_img("btn_leave", ".png");
	irr::video::ITexture	*img1 = database::load_img("btn_continue", ".png");


	if (!img || !bg || !img1)
		throw exception("Impossible to load image");
	_env->clear();
	_env->addImage(bg, irr::core::position2d<irr::s32>(0, 0));
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGame::LEAVE);
	utils::add_button(_env, img1, irr::core::position2di((_config->WINDOW_WIDTH - img1->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img1->getSize().Height), CodeEventGame::CONTINU);
}

void	game::game_menu()
{
	irr::video::ITexture	*img = database::load_img("btn_break", ".png");

	_env->clear();
	if (!img)
		throw exception("Impossible to load image");
	utils::add_button(_env, img, irr::core::position2di(0, 0), CodeEventGame::BREAK);
}

void	game::run()
{
	if (_player && !_break)
		_player->refresh();
	_graphic->getSceneManager()->drawAll();
	_env->drawAll();
}

void	game::generate_floor()
{
	irr::video::ITexture	*ground = database::load_img("ground");
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	std::size_t	y = 0;
	std::size_t	x = 0;
	std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>	line;

	if (!ground || !wall)
		throw exception("Impossible to load image");
	_config->TILE_SIZE = ground->getSize().Height;
	_config->TILE_COUNT = _config->WINDOW_HEIGHT / _config->TILE_SIZE;
	_config->GAME_AREA = _config->TILE_COUNT * _config->TILE_SIZE;
	for (int i = 0;i < _config->TILE_COUNT * _config->TILE_COUNT;i += 1){
		if (i / _config->TILE_COUNT != y){
			_floor.push_back(line);
			line.clear();
			y = i / _config->TILE_COUNT;
		}
		x = i % _config->TILE_COUNT;
		if (x == 0 || y == 0 || x == _config->TILE_COUNT - 1 || y == _config->TILE_COUNT - 1)
			line.push_back(std::make_tuple(x, y, GroundType::WALL, wall));
		else
			line.push_back(std::make_tuple(x, y, GroundType::GROUND, ground));
	}
	if (line.size() > 0)
		_floor.push_back(line);
	generate_map();
	draw_wall();
	set_camera();
}

void 	game::generate_map()
{
	irr::video::ITexture	*brick = database::load_img("brick", ".png");
	std::list<std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>>::iterator	y = _floor.begin();
	std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>::iterator	x;

	if (!brick)
		throw exception("Impossible to load image");
	for (;y != _floor.end();y++){
		x = y->begin();
		for (;x != y->end();x++){
			if (std::get<2>(*x) != GroundType::GROUND)
				continue;
			std::get<2>(*x) = GroundType::BRICK;
			std::get<3>(*x) = brick;
		}
	}
}

void	game::set_camera()
{
	irr::scene::ICameraSceneNode	*cam = _smgr->addCameraSceneNode();
	std::size_t			mid = _config->GAME_AREA / 2;

	cam->setPosition(irr::core::vector3df(mid - _config->TILE_SIZE / 2, _config->GAME_AREA * 0.74, mid));
	cam->setTarget(irr::core::vector3df(mid - _config->TILE_SIZE / 2, 0, mid));
}

void	game::draw_wall()
{
	std::list<std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>>::iterator	y = _floor.begin();
	std::list<std::tuple<int, int, GroundType, irr::video::ITexture *>>::iterator	x;
	irr::scene::IMeshSceneNode *current = nullptr;

	for (;y != _floor.end();y++){
		x = y->begin();
		for (;x != y->end();x++){
			current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
			if (!current)
				continue;
			current->setPosition(irr::core::vector3df(
				std::get<1>(*x) * _config->TILE_SIZE,
				std::get<2>(*x) != GroundType::GROUND ? _config->TILE_SIZE : 0,
				std::get<0>(*x) * _config->TILE_SIZE
			));
			current->setMaterialTexture(0, std::get<3>(*x));
		}
	}
}

void	game::pause()
{
	if (_player)
		_player->pause();
	break_menu();
	_break = true;
}

void	game::play()
{
	game_menu();
	_break = false;
}

player	*game::get_player()
{
	return (_player);
}

bool	game::is_break() const
{
	return (_break);
}

void	game::back_to_main()
{
	_smgr->clear();
	_graphic->setEventReceiver(nullptr);
	_project->set_interface(new gui(_graphic, _config, _project));
}