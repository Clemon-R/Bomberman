/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** game
*/

#ifndef GAME_HPP_
	#define GAME_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/config.hpp"
	#include "project/game/player.hpp"
	#include "project/interface.hpp"
class	project;
	#include "project/project.hpp"
class	game_handler;
	#include "project/game/game_handler.hpp"
	#include "project/game/bomb.hpp"
	#include "project/game/server.hpp"
	#include "project/enum_list.hpp"
	#include <iostream>
	#include <list>
	#include <tuple>
	#include <memory>

class	game : public interface
{
public:
	game(irr::IrrlichtDevice *graphic, config *config, project *project, bool draw = true);
	~game();

	player	*get_player();

	void	run() override final;
	void	pause();
	void	play();

	bool	is_break() const;

	void	game_menu();
	void	break_menu();
	void	save_menu();

	void	back_to_main();

	const std::string	get_text();

	void	save_game(const std::string &filename);
	void	load_game(const std::string &filename);

	void	set_camera();

	std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>	*get_floor(int x, int y);
	std::list<bomb *>	&get_bombs();
	std::list<player *>	get_player_by_pos(int x, int y);

	void	draw_all();
	irr::scene::IMeshSceneNode	*add_wall(std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *> &floor);
private:
	void	full_corner_remove();
	void	corner_remove();

	void	draw_floor();
	void	draw_wall();

	void	generate_floor();
	void	generate_map();

	void	dispatch_load(const std::string &param, const std::string &arg);

	void	save_map(std::ofstream	&file);
	void	load_map(const std::string &map);

	player	*_current;
	std::list<std::unique_ptr<player>>	_players;
	std::list<bomb *>			_bombs;
	std::list<std::list<std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>>>	_floor;

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;
	std::unique_ptr<game_handler>	_handler;
	config			*_config;
	bool			_break;
	project	*_project;
	irr::gui::IGUIEditBox	*_text;
	server			*_server;
};
#endif /* !GAME_HPP_ */
