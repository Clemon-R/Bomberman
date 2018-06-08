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
	#include "project/enum_list.hpp"
	#include <iostream>
	#include <list>
	#include <tuple>
	#include <memory>

using	TYPE_FLOOR = std::tuple<int, int, GroundType, irr::video::ITexture *, irr::scene::IMeshSceneNode *>;

class	game : public interface
{
public:
	game(irr::IrrlichtDevice *graphic, config *config, project *project, bool multiplayer, bool draw = true);
	~game();

	player	*get_player(int number);

	void	run() override final;
	void	pause();
	void	play();

	void	game_menu();
	void	break_menu();
	void	save_menu();

	void	back_to_main();

	const std::string	get_text();

	void	save_game(const std::string &filename);
	void	load_game(const std::string &filename);


	TYPE_FLOOR	*get_floor(int x, int y);
	std::list<std::list<TYPE_FLOOR>>	&get_floors();
	std::list<bomb *>	&get_bombs();
	std::list<player *>	get_player_by_pos(int x, int y);
	bool	is_break() const;
	void	set_camera();

	void	draw_all();
	irr::scene::IMeshSceneNode	*add_wall(TYPE_FLOOR &floor);
	project	&get_project();
	player	*get_current();
private:
	void	create_players();

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
	player	*_current2;
	bool	_multiplayer;
	bool	_break;
	std::list<std::unique_ptr<player>>	_players;
	std::list<bomb *>			_bombs;
	std::list<std::list<TYPE_FLOOR>>	_floor;
	irr::scene::ICameraSceneNode		*_camera;

	irr::IrrlichtDevice		*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	irr::scene::ISceneManager	*_smgr;
	std::unique_ptr<game_handler>	_handler;
	config				*_config;
	project				*_project;
	irr::gui::IGUIEditBox		*_text;
};
#endif /* !GAME_HPP_ */
