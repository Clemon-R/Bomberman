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
	#include "project/game/game.hpp"
	#include <iostream>
	#include <memory>

enum	GuiState
{
	MAIN,
	GAME,
	BREAK
};

class	gui : public interface
{
public:
	gui(irr::IrrlichtDevice *graphic, config *config);
	~gui();

	void	run() override;
	void	set_state(GuiState state);
private:
	void	run_gui();
	void	run_game();

	void	main_menu();
	void	break_menu();
	void	game_menu();

	irr::IrrlichtDevice	*_graphic;
	irr::video::IVideoDriver	*_driver;
	irr::gui::IGUIEnvironment	*_env;
	std::unique_ptr<gui_handler>	_handler;
	std::unique_ptr<game>		_game;
	config			*_config;
	GuiState		_state;
};
#endif /* !GUI_HPP_ */
