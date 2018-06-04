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
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

game::game(irr::IrrlichtDevice *graphic, config *config, project *project, bool draw) : _graphic(graphic), _config(config),
_break(false), _current(nullptr), _project(project), _handler(new game_handler(graphic, *this)), _camera(nullptr)
{
	std::cout << "game: init...\n";
	_driver = _graphic->getVideoDriver();
	_env = _graphic->getGUIEnvironment();
    	_smgr = _graphic->getSceneManager();
	if (!_driver || !_env || !_smgr)
		throw exception("Impossible to find the driver");
	generate_floor();
	for (int i = 0;i < 4;i += 1){
		_players.push_back(std::make_unique<player>(i, this, _graphic, _config));
		_players.back()->set_position(irr::core::position2di(i % 2 * (_config->TILE_COUNT - 3) + 1, i / 2 * (_config->TILE_COUNT - 3) + 1));
		_players.back()->set_rotation(i / 2 * 180);
		if (i < 3)
			_players.back()->set_ia();
	}
	_current = _players.back().get();
	game_menu();
	if (draw)
		draw_all();
	_graphic->setEventReceiver(_handler.get());
	std::cout << "game: initiated\n";
}

game::~game()
{
	std::cout << "game: destroying\n";
	for (auto &player : _players)
		player.reset(nullptr);
	_handler.reset(nullptr);
	std::cout << "game: destroyed\n";
}

void	game::break_menu()
{
	irr::video::ITexture	*bg = database::load_img("break", ".png");
	irr::video::ITexture	*img = database::load_img("btn_leave", ".png");
	irr::video::ITexture	*img1 = database::load_img("btn_continue", ".png");
	irr::video::ITexture	*img2 = database::load_img("btn_save", ".png");

	std::cout << "game: break menu\n";
	if (!img || !bg || !img1 || !img2)
		throw exception("Impossible to load image");
	_env->clear();
	_env->addImage(bg, irr::core::position2d<irr::s32>(0, 0));
	utils::add_button(_env, img1, irr::core::position2di((_config->WINDOW_WIDTH - img1->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 - img1->getSize().Height), CodeEventGame::CONTINU);
	utils::add_button(_env, img2, irr::core::position2di((_config->WINDOW_WIDTH - img2->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img2->getSize().Height / 2), CodeEventGame::SAVE);
	utils::add_button(_env, img, irr::core::position2di((_config->WINDOW_WIDTH - img->getSize().Width) / 2, _config->WINDOW_HEIGHT / 2 + img->getSize().Height * 2), CodeEventGame::LEAVE);
}

void	game::save_menu()
{
	irr::video::ITexture	*bg = database::load_img("break", ".png");
	irr::video::ITexture	*img = database::load_img("btn_save", ".png");
	irr::video::ITexture	*img1 = database::load_img("btn_back", ".png");
	std::size_t	x = 0;

	if (!bg || !img || !img1)
		throw exception("Impossible to load image");
	x = (_config->WINDOW_WIDTH - img1->getSize().Width) / 2;
	_env->clear();
	_env->addImage(bg, irr::core::position2d<irr::s32>(0, 0));
	_text = _env->addEditBox(L"", irr::core::recti(x, _config->WINDOW_HEIGHT / 2 - img1->getSize().Height, x + img->getSize().Width, _config->WINDOW_HEIGHT / 2));
	utils::add_button(_env, img, irr::core::position2di(x, _config->WINDOW_HEIGHT / 2 + img->getSize().Height / 2), CodeEventGame::SAVEGAME);
	utils::add_button(_env, img1, irr::core::position2di(x, _config->WINDOW_HEIGHT / 2 + img1->getSize().Height * 2), CodeEventGame::BACKGAME);
}

void	game::game_menu()
{
	irr::video::ITexture	*img = database::load_img("btn_break", ".png");

	std::cout << "game: game menu\n";
	if (!img)
		throw exception("Impossible to load image");
	_env->clear();
	utils::add_button(_env, img, irr::core::position2di(0, 0), CodeEventGame::BREAK);
}

void	game::back_to_main()
{
	std::cout << "game: back to the main\n";
	_smgr->clear();
	_graphic->setEventReceiver(nullptr);
	_project->set_interface(new gui(_graphic, _config, _project));
}

void	game::run()
{
	auto	bomb = _bombs.begin();

	_smgr->drawAll();
	_env->drawAll();
	if (_break)
		return;
	for (;bomb != _bombs.end();bomb++){
		if (!(*bomb)->run())
			bomb = _bombs.erase(bomb);
	}
	for (auto &player : _players)
		if (player->is_alive())
			player->refresh();
		else if (!_camera)
			set_camera();
}

void	game::generate_floor()
{
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	std::size_t	y = 0;
	std::size_t	x = 0;
	std::list<std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>>	line;

	std::cout << "game: generating map...\n";
	if (!wall)
		throw exception("Impossible to load image");
	_config->TILE_SIZE = wall->getSize().Height;
	_config->TILE_COUNT = _config->WINDOW_HEIGHT / _config->TILE_SIZE;
	_config->GAME_AREA = _config->TILE_COUNT * _config->TILE_SIZE;
	for (int i = 0;i < _config->TILE_COUNT * _config->TILE_COUNT;i += 1){
		if (i / _config->TILE_COUNT != y){
			_floor.push_back(line);
			line.clear();
			y += 1;
			x = 0;
		}
		if (x == 0 || y == 0 || x == _config->TILE_COUNT - 1 || y == _config->TILE_COUNT - 1)
			line.push_back(std::make_tuple(x, y, GroundType::WALL, wall, nullptr));
		else
			line.push_back(std::make_tuple(x, y, GroundType::NONE, nullptr, nullptr));
		x += 1;
	}
	if (line.size() > 0)
		_floor.push_back(line);
	generate_map();
	std::cout << "game: map generated\n";
}

void    game::full_corner_remove()
{
	auto	y = _floor.begin();
	auto	x = y->begin();

	for (;y != _floor.end();y++){
		x = y->begin();
		for (;x != y->end();x++){
		if ((std::get<0>(*x) == 2 && std::get<1>(*x) == 1) ||
			(std::get<0>(*x) == 1 && std::get<1>(*x) == 2) ||
			(std::get<0>(*x) == 1 && std::get<1>(*x) == _config->TILE_COUNT - 3) ||
			(std::get<0>(*x) == 2 && std::get<1>(*x) == _config->TILE_COUNT - 2) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 3 && std::get<1>(*x) == 1) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 2 && std::get<1>(*x) == 2) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 3 && std::get<1>(*x) == _config->TILE_COUNT - 2) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 2 && std::get<1>(*x) == _config->TILE_COUNT - 3)){
			std::get<2>(*x) = GroundType::NONE;
			std::get<3>(*x) = nullptr;
		}
		else
			continue;
		}
	}
}

void    game::corner_remove()
{
	auto	y = _floor.begin();
	auto	x = y->begin();
	
	for (;y != _floor.end();y++){
		x = y->begin();
		for (;x != y->end();x++){
		if ((std::get<0>(*x) == 1 && std::get<1>(*x) == 1) || 
			(std::get<0>(*x) == 1 && std::get<1>(*x) == _config->TILE_COUNT - 2) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 2 && std::get<1>(*x) == 1) ||
			(std::get<0>(*x) == _config->TILE_COUNT - 2 && std::get<1>(*x) == _config->TILE_COUNT - 2)){
			std::get<2>(*x) = GroundType::NONE;
			std::get<3>(*x) = nullptr;
		}
		else
			continue;
		}
	}
	full_corner_remove();
}

void     game::generate_map()
{
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	irr::video::ITexture	*brick = database::load_img("bric", ".png");
	auto	y = _floor.begin();
	auto	x = y->begin();

	if (!brick)
		throw exception("Impossible to load image");
	for (;y != _floor.end();y++){
		for (x = y->begin();x != y->end();x++){
			if (std::get<2>(*x) != GroundType::NONE)
				continue;
			if (rand() % 4 == 1){
				std::get<2>(*x) = GroundType::WALL;
				std::get<3>(*x) = wall;
				continue;
			}
			std::get<2>(*x) = GroundType::BRICK;
			std::get<3>(*x) = brick;
		}
	}
	corner_remove();
}

void	game::set_camera()
{
	std::size_t			mid = _config->GAME_AREA / 2;

	std::cout << "game: adding the camera...\n";
	_camera = _smgr->addCameraSceneNode();
	if (!_camera)
		return;
	_camera->setPosition(irr::core::vector3df(mid - _config->TILE_SIZE / 2, _config->GAME_AREA * 0.74, mid));
	_camera->setTarget(irr::core::vector3df(mid - _config->TILE_SIZE / 2, 0, mid));
	std::cout << "game: camera added\n";
}


irr::scene::IMeshSceneNode	*game::add_wall(std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *> &floor)
{
	irr::scene::IMeshSceneNode	*current = nullptr;

	if (std::get<2>(floor) == GroundType::NONE)
		return (nullptr);
	current =  _smgr->addCubeSceneNode(_config->TILE_SIZE);
	if (!current)
		return (nullptr);
	current->setPosition(irr::core::vector3df(
		std::get<1>(floor) * _config->TILE_SIZE,
		_config->TILE_SIZE,
		std::get<0>(floor) * _config->TILE_SIZE
	));
	current->setMaterialTexture(0, std::get<3>(floor));
	current->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	std::get<4>(floor) = current;
	return (current);
}

/**
 * Drawing the ground
 **/

void	game::draw_floor()
{
	auto	y = _floor.begin();
	auto	x = y->begin();
	irr::scene::IMeshSceneNode	*current = nullptr;
	irr::video::ITexture	*ground = database::load_img("ground");

	std::cout << "game: spawning floor...\n";
	if (!ground)
		throw exception("Impossible to load ground");
	for (;y != _floor.end();y++){
		for (x = y->begin();x != y->end();x++){
			current = _smgr->addCubeSceneNode(_config->TILE_SIZE);
			if (!current)
				continue;
			current->setPosition(irr::core::vector3df(
				std::get<1>(*x) * _config->TILE_SIZE,
				0,
				std::get<0>(*x) * _config->TILE_SIZE
			));
			current->setMaterialTexture(0, ground);
    			current->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}
	}
	std::cout << "game: floor spawned\n";
}

/**
 * Drawing all block on the ground
 **/

void	game::draw_wall()
{
	auto	y = _floor.rbegin();
	auto	x = y->begin();
	irr::scene::IMeshSceneNode *current = nullptr;

	std::cout << "game: spawning wall...\n";
	for (;y != _floor.rend();y++){
		for (x = y->begin();x != y->end();x++){
			if (std::get<2>(*x) == GroundType::NONE)
				continue;
			add_wall(*x);
		}
	}
	std::cout << "game: wall spawned\n";
}

/**
 * Drawing the ground and blocks
 **/

void	game::draw_all()
{
	auto	y = _floor.rbegin();
	auto	x = y->begin();
	irr::scene::IMeshSceneNode *current = nullptr;
	irr::video::ITexture	*ground = database::load_img("ground");

	std::cout << "game: spawning map...\n";
	if (!ground)
		throw exception("Impossible to load ground");
	_smgr->clear();
	draw_floor();
	draw_wall();
	for (const auto &player : _players)
		player->spawn();
	if (_current->is_alive())
		_current->set_camera();
	else
		set_camera();
	std::cout << "game: map spawned\n";
}


/**
 * Pause the game
 **/

void	game::pause()
{
	std::cout << "game: pause\n";
	for (auto &p : _players)
		p->pause();
	break_menu();
	_break = true;
}


/**
 * Continue the game
 **/

void	game::play()
{
	std::cout << "game: continue\n";
	game_menu();
	_break = false;
}

/**
 * Load the map with a list of enum
 **/

void	game::load_map(const std::string &map)
{
	std::stringstream	ss;
	std::string		val;
	int			value = -1;
	irr::video::ITexture	*wall = database::load_img("wall", ".png");
	irr::video::ITexture	*bric = database::load_img("bric", ".png");
	auto	y = _floor.begin();
	auto	x = y->begin();

	std::cout << "game: loading map...\n";
	if (!wall || !bric)
		throw exception("Impossible to load image");
	ss.str(map);
	while (std::getline(ss, val, ',')){
		value = std::atoi(val.c_str());
		switch (value){
			case GroundType::WALL:
			std::get<2>(*x) = GroundType::WALL;
			std::get<3>(*x) = wall;
			break;

			case GroundType::BRICK:
			std::get<2>(*x) = GroundType::BRICK;
			std::get<3>(*x) = bric;
			break;

			default:
			std::get<2>(*x) = GroundType::NONE;
			std::get<3>(*x) = nullptr;
			break;
		}
		x++;
		if (x == y->end()){
			y++;
			if (y == _floor.end())
				break;
			x = y->begin();
		}

	}
	std::cout << "game: map loaded\n";
}

/**
 * Dispatch param of save file
 **/

void	game::dispatch_load(const std::string &param, const std::string &arg)
{
	std::regex	e("P([0-9])+_(.+)");
	std::smatch	matchs;

	std::cout << "game: dispatch param - " << param << std::endl;
	if (std::regex_search(param, matchs, e)){
		for (auto &p : _players)
			if (p->get_id() == std::atoi(matchs[1].str().c_str()))
				p->load_player(matchs[2], arg);
	} else if (param.compare("MAP") == 0)
		load_map(arg);
}

void	game::load_game(const std::string &filename)
{
	std::ifstream	file;
	std::string	line;
	std::smatch	matchs;
	std::regex	e("(.+)=(.+)");

	std::cout << "game: loading...\n";
	file.open(filename);
	if (!file.is_open())
		throw exception("Impossible to load the save");
	while (std::getline(file, line)){
		while (std::regex_search(line, matchs, e)){
			dispatch_load(matchs[1], matchs[2]);
			line = matchs.suffix().str();
		}
	}
	draw_all();
	file.close();
	std::cout << "game: loaded\n";
}

void	game::save_map(std::ofstream &file)
{
	auto	y = _floor.begin();
	auto	x = y->begin();
	bool	first = true;

	std::cout << "game: saving map...\n";
	file << "MAP=";
	for (;y != _floor.end();y++){
		for (x = y->begin();x != y->end();x++, first = false){
			if (!first)
				file << ",";
			file << std::get<2>(*x);
		}
	}
	file << std::endl;
	std::cout << "game: map saved\n";
}

void	game::save_game(const std::string &filename)
{
	std::ofstream	file;

	std::cout << "game: saving...\n";
	std::cout << "game: removing old save if exist...\n";
	remove(filename.c_str());
	file.open(filename);
	if (!file.is_open())
		throw exception("Impossible to write the save");
	save_map(file);
	for (auto &p : _players)
		p->save_player(file);
	file.close();
	std::cout << "game: saved\n";
}

/**
 * Get the one cellule by pos
 **/

std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>	*game::get_floor(int x, int y)
{
	for (auto &elem : _floor){
		for (auto &floor : elem){
			if (std::get<0>(floor) == x && std::get<1>(floor) == y)
				return (&floor);
		}
	}
	return (nullptr);
}

std::list<std::list<TYPE_FLOOR>>	&game::get_floors()
{
	return (_floor);
}

/**
 * Get a list of player by pos x/y
 **/

std::list<player *>	game::get_player_by_pos(int x, int y)
{
	irr::core::position2di	pos;
	std::list<player *>	result;

	for (auto &elem : _players){
		pos = elem->get_position();
		if (pos.X == x && pos.Y == y)
			result.push_back(elem.get());
	}
	return (result);
}

/**
 * All getter
 **/

std::list<bomb *>	&game::get_bombs()
{
	return (_bombs);
}

player	*game::get_player()
{
	return (_current);
}

bool	game::is_break() const
{
	return (_break);
}

const std::string	game::get_text()
{
	std::string	result;

	for (int i = 0;_text && _text->getText() && _text->getText()[i];i++){
		result += _text->getText()[i];
	}
	return (result);
}