/*
** EPITECH PROJECT, 2018
** indie studio
** File description:
** gui
*/

#ifndef GUI_HPP_
	#define GUI_HPP_

	#include "irrlicht/irrlicht.h"
	#include "project/interface.hpp"
	#include "project/config.hpp"
class	gui_handler;
	#include "project/gui/gui_handler.hpp"
class	game;
	#include "project/game/game.hpp"
class	project;
	#include "project/project.hpp"
	#include <iostream>
	#include <memory>

class	gui : public interface
{
public:
	gui(irr::IrrlichtDevice *graphic, config *config, project *project);
	~gui();

	void	run() override final;
	void	play_game();
	void	play_multiplayer_game();
	
	void	main_menu();
	void	load_menu();

	void	load_game(const std::string &filename);

	const std::string	get_text();
	project			&get_project();
private:
	irr::IrrlichtDevice	*_graphic;
	irrklang::ISound	*_sound;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	std::unique_ptr<gui_handler>	_handler;
	config			*_config;
	project			*_project;
	irr::gui::IGUIEditBox	*_text;
};
#endif /* !GUI_HPP_ */
